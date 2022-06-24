#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <dirent.h>
#include <netinet/in.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>

const char *LOCK_FILE = "/tmp/fbtHttpd.lock";

// Content types
const char *TEXT_CSS = "text/css";
const char *TEXT_HTML = "text/html";
const char *TEXT_PLAIN = "text/plain";
const char *IMAGE_PNG = "image/png";
const char *IMAGE_JPEG = "image/jpeg";
const char *APPLICATION_OCTET_STREAM = "application/octet-stream";
const char *APPLICATION_PDF = "application/pdf";

const char *OK = "200 OK";
const char *FileNotFound = "404 FileNotFound";

int fulfilled_requests = 0;

std::string www_path;
uint16_t port;

std::string generate_header(
                            const char *response,
                            int content_length,
                            const char *content_type)
{
    const char* ENDL = "\r\n";
    
    std::ostringstream os;
    os << "HTTP/1.1 " << response << ENDL
       << "Connection: close" << ENDL
       << "Content-Language: de" << ENDL
       << "Content-Length: " << content_length << ENDL
       << "Content-Type: " << content_type << ENDL
       << ENDL;

    return os.str();
}

std::string get_response(std::string &resource)
{
    std::string resource_absolute = www_path + resource;
    
    std::ostringstream os;

    struct stat s;
    if (stat(resource_absolute.c_str(), &s) == 0) {
        if (S_ISREG(s.st_mode)) {
            const char *content_type = APPLICATION_OCTET_STREAM;
            
            size_t sep = resource.find_last_of(".");
            if (sep != std::string::npos)
            {
                std::string ext = resource.substr(sep + 1, resource.size() - sep - 1);
                std::transform(ext.begin(), ext.end(), ext.begin(),
                               [](unsigned char c) { return std::tolower(c); });
                if (ext == "htm" || ext == "html") {
                    content_type = TEXT_HTML;
                } else if (ext == "txt" || ext == "h" || ext == "c" || ext == "c++") {
                    content_type = TEXT_PLAIN;
                } else if (ext == "pdf") {
                    content_type = APPLICATION_PDF;
                } else if (ext == "png") {
                    content_type = IMAGE_PNG;
                } else if (ext == "jpg" || ext == "jpeg") {
                    content_type = IMAGE_JPEG;
                } else if (ext == "css") {
                    content_type = TEXT_CSS;
                }
            }

            std::ifstream file(resource_absolute);
            os << generate_header(OK, s.st_size, content_type)
               << file.rdbuf();
            file.close();
        } else if (S_ISDIR(s.st_mode)) {
            std::string index_resource = resource + "/index.html";
            std::string index_resource_absolute = www_path + index_resource;
            
            struct stat index_stat;
            if (stat(index_resource_absolute.c_str(), &index_stat) == 0) {
                return get_response(index_resource);
            }
        
            std::ostringstream os_html;
            os_html << "<html>"
                    << "  <body>"
                    << "    <table>";

            DIR *dirp = opendir(resource_absolute.c_str());
            while (dirp != nullptr) {
                dirent *dp = readdir(dirp);
                if (dp != nullptr) {
                    std::string target = resource + dp->d_name;
                    os_html << "<tr>"
                            << "  <td>"
                            << "<a href=\"" << resource.c_str() << "\">" << dp->d_name << "</a>"
                            << "  </td>"
                            << "</tr>";
                } else {
                    closedir(dirp);
                    dirp = nullptr;
                }
            }

            os_html << "    </table>"
                    << "  </body>"
                    << "</html>";

            std::string html = os_html.str();

            os << generate_header(OK, html.length(), TEXT_HTML)
               << html;
        }
    } else {
        std::ostringstream os_html;
        os_html << "<html>"
                << "<body>"
                << "File not found"
                << "</body>"
                << "</html>";
        std::string html = os_html.str();
            
        os << generate_header(OK, html.length(), TEXT_HTML)
           << html;
    }
    
    return os.str();
}

void handle(int socketfd)
{
    const int BUFFER_SIZE = 100;
    const char GET[] = "GET";

    const int GET_LEN = strlen(GET);
    
    enum {METHOD, RESOURCE, DONE, FAIL} state = METHOD;
    char buffer[BUFFER_SIZE];
    int index = 0;
    std::string resource;
    while (recv(socketfd, &buffer, 100, 0) >= 0 && state < DONE) {
        if (state == METHOD) {
            if (strncmp(buffer, GET, GET_LEN) == 0) {
                state = RESOURCE;
                index += GET_LEN + 1;
            } else {
                state = FAIL;
            }
        }
        if (state == RESOURCE) {
            char *res = &buffer[index];
            char *end = strstr(res, " ");
            int len;
            if (end != nullptr) {
                len = end - res;
                state = DONE;
            } else {
                len = BUFFER_SIZE - index;
            }
            resource = std::string(res, len);
        }
        index = 0;
    }

    std::string response = get_response(resource);
    send(socketfd, response.c_str(), response.length(), 0);
    fulfilled_requests++;
}

int run(int socketfd)
{
    int reuse = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        syslog(LOG_ERR, "Socket option SO_REUSEADDR konnte nicht gesetzt werden\n");
        return -1;
    }

    #ifdef SO_REUSEPORT
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
        syslog(LOG_ERR, "Socket option SO_REUSEPORT konnte nicht gesetzt werden\n");
        return -1;
    }
    #endif

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        syslog(LOG_ERR, "Addresse / Port konnten nicht gebunden werden\n");
        return -1;
    }

    if (listen(socketfd, 8) < 0) {
        syslog(LOG_ERR, "Listen fehlgeschlagen\n");
        return -1;
    }
    while (true) {
        int connection = accept(socketfd, nullptr, nullptr);  
        if (connection < 0) {
            syslog(LOG_ERR, "Accept fehlgeschlagen\n");
            return -1;
        }

        handle(connection);
        
        if (close(connection) < 0) {
            syslog(LOG_ERR, "Close fehlgeschlagen\n");
        }
    }

    return 0;
}

int set_sig_handler(int sig, sighandler_t handler)
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    return sigaction(sig, &action, nullptr);
}

void handle_sighup(int signum)
{
    syslog(LOG_INFO, "fbtHttpd: Running (%s, %d)", www_path.c_str(), fulfilled_requests);
}

void handle_sigterm(int signum)
{
    syslog(LOG_INFO, "fbtHttpd: Stopping (%s, %d)", www_path.c_str(), fulfilled_requests);
    remove(LOCK_FILE);
}

bool init_daemon()
{
    pid_t pid = fork();
    if (pid != 0) {
        return false;
    }

    if (setsid() < 0) {
        std::cerr << "Cannot set new session\n";
        return false;
    }

    set_sig_handler(SIGHUP, handle_sighup);
    set_sig_handler(SIGTERM, handle_sigterm);

    chdir("/");
    umask(0);

    openlog("Temperatur-Daemon", 0, LOG_USER);

    return true;
}

int main(int argc, char *argv[])
{
    if (open(LOCK_FILE, O_CREAT | O_EXCL) < 0) {
        std::cerr << "Daemon läuft bereits\n";
        return -1;
    }
    
    if (argc < 2) {
        std::cout << "Usage: fbtHttpd <www-path> <port>\n";
        return -1;
    }

    www_path = std::string(argv[1]);
    port = strtoul(argv[2], nullptr, 0);

    if (!init_daemon()) {
        return 0;
    }

    syslog(LOG_INFO, "Starting daemon\n");

    int skt = socket(AF_INET, SOCK_STREAM, 0);
    if (skt < 0) {
        syslog(LOG_ERR, "Socket konnte nicht erstellt werden\n");
        return -1;
    }

    int result = run(skt);

    if (close(skt) < 0) {
        syslog(LOG_ERR, "Close fehlgeschlagen\n");
    }
    
    return result;
}

let projects = []
let sorter = new ProjectSorter()

function updateProjects() {
    const table = document.getElementById('overviewtable')
    for (const project of projects) {
        table.innerHTML += '\n' +
            `<tr id="project-${project.id}">\n` +
            `  <td class="title">${project.title}</td>\n` +
            `  <td class="short_description">${project.description}</td>\n` +
            `  <td>${project.date}</td>\n` +
            '  <td>\n' +
            `    <a href="project.html?id=${project.id}">Zur Projektseite</a>\n` +
            '  </td>\n' +
            '</tr>'
    }
}

window.addEventListener('load', async function () {
    const api = new ProjectApi()
    projects = await api.all()
    console.log(projects)

    sorter.sortProjects(projects)

    updateProjects()
})
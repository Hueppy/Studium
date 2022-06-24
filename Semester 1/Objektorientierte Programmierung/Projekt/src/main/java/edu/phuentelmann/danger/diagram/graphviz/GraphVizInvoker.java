package edu.phuentelmann.danger.diagram.graphviz;

import java.io.*;
import java.nio.file.Paths;
import java.util.List;

/**
 * Invokes "dot" application with specific parameters to generate SVG from input DOT
 */
public class GraphVizInvoker {
    public interface Request {
        void accept(OutputStream in) throws Exception; // <- take this java
    }

    public interface Response {
        void accept(InputStream out, InputStream err) throws Exception;
    }

    public GraphVizInvoker() {
        pb = new ProcessBuilder();
        pb.directory(Paths.get("").toAbsolutePath().toFile());
        pb.command(List.of("dot", "-Tsvg", "-o" + OUTPUT_FILENAME, INPUT_FILENAME));
    }

    private static final String INPUT_FILENAME = "temp.dot";
    private static final String OUTPUT_FILENAME = "temp.svg";
    private final ProcessBuilder pb;

    public void invoke(Request req, Response res) throws Exception {
        //Process p = pb.start();

        //try (final OutputStream in = p.getOutputStream()) {
        try (final FileOutputStream in = new FileOutputStream(INPUT_FILENAME)) {
            req.accept(in);
        }

        Process p = pb.start();
        p.waitFor();

        //final InputStream out = p.getInputStream();
        final InputStream err = p.getErrorStream();
        try (final InputStream out = new FileInputStream(OUTPUT_FILENAME)) {
            res.accept(out, err);
        }
    }
}

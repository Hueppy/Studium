package edu.phuentelmann.danger.diagram.graphviz;

import java.awt.Color;
import java.io.PrintStream;
import java.util.Formatter;
import java.util.Locale;
import java.util.function.Function;

import edu.phuentelmann.danger.utils.Lazy;

/**
 * Visitor for converting graph model to DOT
 */
public class DotGraphVisitor extends GraphScanner<PrintStream> {
    private boolean inEdge = false;
    private boolean inNode = false;
    private Graph.Type type;

    private String formatColor(Color c) {
        return "\"#%02x%02x%02x%02x\"".formatted(c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha());
    }

    private String getEdge() {
        if (type == Graph.Type.Undirected) {
            return "--";
        }
        return "->";
    }

    @Override
    public void visit(Graph g, PrintStream s) {
        type = g.getType();

        switch (type) {
            case Undirected:
                s.print("graph");
            case Directed:
                s.print("digraph");
        }

        s.println(" G {");
        super.visit(g, s);
        s.println("}");
    }

    @Override
    public void visit(Edge e, PrintStream s) {
        inEdge = true;
        try {
            s.print(String.format(Locale.ROOT, "\"%s\" %s \"%s\" ", e.getSource(), getEdge(), e.getTarget()));
            super.visit(e, s);
            s.println();
        } finally {
            inEdge = false;
        }
    }

    @Override
    public void visit(Node n, PrintStream s) {
        inNode = true;
        try {
            s.print(String.format(Locale.ROOT, "\"%s\" ", n.getName()));
            super.visit(n, s);
            s.println();
        } finally {
            inNode = false;
        }
    }
    
    @Override
    public void visit(Graph.Attributes a, PrintStream s) {
        final Graph.Attributes parent = a.getParent();
        if (!a.getFontName().equals(parent.getFontName())) s.println(String.format(Locale.ROOT, "fontname=\"%s\"", a.getFontName()));
        if (a.getFontSize() != parent.getFontSize())       s.println(String.format(Locale.ROOT, "fontsize=%s", a.getFontSize()));
        if (a.getRankDir() != parent.getRankDir())         s.println(String.format(Locale.ROOT, "rankdir=%s", a.getRankDir()));
        if (a.getSplines() != parent.getSplines())         s.println(String.format(Locale.ROOT, "splines=%s", a.getSplines()));
        if (a.getNodesep() != parent.getNodesep())         s.println(String.format(Locale.ROOT, "nodesep=%s", a.getNodesep()));
        if (a.getRanksep() != parent.getRanksep())         s.println(String.format(Locale.ROOT, "ranksep=%s", a.getRanksep()));
    }

    @Override
    public void visit(Node.Attributes a, PrintStream s) {
        final Lazy<PrintStream> out = new Lazy<>(() -> {
            if (!inNode) {
                s.print("node ");
            }

            s.println("[");
            return s;
        });

        final Node.Attributes parent = a.getParent();
        if (a.getColor() != parent.getColor())             out.get().println(String.format(Locale.ROOT, "color=%s", formatColor(a.getColor())));
        if (!a.getLabel().equals(parent.getLabel()))       out.get().println(String.format(Locale.ROOT, "label=\"%s\"", a.getLabel().replace("<", "&lt;").replace(">", "&gt;")));
        if (a.getShape() != parent.getShape())             out.get().println(String.format(Locale.ROOT, "shape=%s\n", a.getShape()));
        if (!a.getFontName().equals(parent.getFontName())) out.get().println(String.format(Locale.ROOT, "fontname=\"%s\"", a.getFontName()));
        if (a.getFontSize() != parent.getFontSize())       out.get().println(String.format(Locale.ROOT, "fontsize=%s\n", a.getFontSize()));
        if (a.getWidth() != parent.getWidth())             out.get().println(String.format(Locale.ROOT, "width=%s\n", a.getWidth()));
        if (a.getHeight() != parent.getHeight())           out.get().println(String.format(Locale.ROOT, "height=%s\n", a.getHeight()));

        if (out.isValueCreated()) {
            s.println("]");
        }
    }

    @Override
    public void visit(Edge.Attributes a, PrintStream s) {
        final Lazy<PrintStream> out = new Lazy<>(() -> {
            if (!inEdge) {
                s.print("edge ");
            }

            s.println("[");
            return s;
        });

        final Edge.Attributes parent = a.getParent();
        if (a.getColor() != parent.getColor())         out.get().println(String.format(Locale.ROOT, "color=%s", formatColor(a.getColor())));
        if (a.getStyle() != parent.getStyle())         out.get().println(String.format(Locale.ROOT, "style=%s", a.getStyle()));
        if (a.getDirection() != parent.getDirection()) out.get().println(String.format(Locale.ROOT, "dir=%s", a.getDirection()));
        if (!a.getHead().equals(parent.getHead()))     out.get().println(String.format(Locale.ROOT, "arrowhead=%s", a.getHead()));
        if (!a.getTail().equals(parent.getTail()))     out.get().println(String.format(Locale.ROOT, "arrowtail=%s", a.getTail()));

        if (out.isValueCreated()) {
            s.println("]");
        }
    }
    
}

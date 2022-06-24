package edu.phuentelmann.danger.diagram.graphviz;

import java.util.List;
import java.util.Stack;

/**
 * Graph model.
 * Consists of nodes and edges and their attributes.
 */
public class Graph {
    public enum Type {
        Undirected,
        Directed
    }

    public static abstract class Statement {
        public abstract <T> void accept(GraphVisitor<T> visitor, T t);
    }

    public static class Attributes extends Statement {
        public enum RankDirection {
            TopBottom("TB"),
            LeftRight("LR"),
            BottomTop("BT"),
            RightLeft("RL");

            RankDirection(String name) {
                this.name = name;
            }

            private String name;

            @Override
            public String toString() {
                return name;
            }
        }

        public enum Splines {
            None,
            Line,
            Polyline,
            Curved,
            Ortho,
            Spline;

            @Override
            public String toString() {
                return name().toLowerCase();
            }
        }

        private Attributes() {
            rankDir = RankDirection.TopBottom;
            fontSize = 14.0;
            fontName = "";
        }

        private Attributes(Attributes parent) {
            this.parent = parent;
            rankDir = parent.rankDir;
            fontSize = parent.fontSize; 
            fontName = parent.fontName;
        }

        public static final Attributes DEFAULT = new Attributes();

        private Attributes parent;

        private RankDirection rankDir;
        private double fontSize;
        private String fontName;
        private Splines splines;
        private double nodesep;
        private double ranksep;

        public Attributes createChild() {
            return new Attributes(this);
        }

        public <T> void accept(GraphVisitor<T> visitor, T t) {
            visitor.visit(this, t);
        }

        public Attributes getParent() {
            return parent;
        }

        public RankDirection getRankDir() {
            return rankDir;
        }

        public void setRankDir(RankDirection rankDir) {
            this.rankDir = rankDir;
        }

        public double getFontSize() {
            return fontSize;
        }

        public void setFontSize(double fontSize) {
            this.fontSize = fontSize;
        }

        public String getFontName() {
            return fontName;
        }

        public void setFontName(String f) {
            fontName = f;
        }

        public Splines getSplines() {
            return splines;
        }

        public void setSplines(Splines s) {
            splines = s;
        }

        public double getNodesep() {
            return nodesep;
        }

        public void setNodesep(double nodesep) {
            this.nodesep = nodesep;
        }

        public double getRanksep() {
            return ranksep;
        }

        public void setRanksep(double ranksep) {
            this.ranksep = ranksep;
        }
    }

    public Graph(Type type) {
        this.type = type;
        this.statements = new Stack<>();
        this.graphAttributes = Attributes.DEFAULT.createChild();
        this.nodeAttributes = Node.Attributes.DEFAULT.createChild();
        this.edgeAttributes = Edge.Attributes.DEFAULT.createChild();
    }

    private final Type type;
    private final Stack<Statement> statements;
    private Attributes graphAttributes;
    private Node.Attributes nodeAttributes;
    private Edge.Attributes edgeAttributes;

    public Node addNode(String name) {
        Node n = new Node(nodeAttributes.createChild(), name);
        statements.push(n);
        return n;
    }

    public Edge addEdge(String source, String target) {
        Edge e = new Edge(source, target, edgeAttributes.createChild());
        statements.push(e);
        return e;
    }

    public Attributes changeAttributes() {
        if (statements.empty() || statements.peek() != graphAttributes) {
            graphAttributes = graphAttributes.createChild();
            statements.push(graphAttributes);
        }
        return graphAttributes;
    }

    public Node.Attributes changeNodeAttributes() {
        if (statements.empty() || statements.peek() != nodeAttributes) {
            nodeAttributes = nodeAttributes.createChild();
            statements.push(nodeAttributes);
        }
        return nodeAttributes;
    }

    public Edge.Attributes changeEdgeAttributes() {
        if (statements.empty() || statements.peek() != edgeAttributes) {
            edgeAttributes = edgeAttributes.createChild();
            statements.push(edgeAttributes);
        }
        return edgeAttributes;
    }

    public <T> void accept(GraphVisitor<T> visitor, T t) {
        visitor.visit(this, t);
    }

    public Type getType() {
        return type;
    }

    public List<Statement> getStatements() {
        return statements;
    }
}

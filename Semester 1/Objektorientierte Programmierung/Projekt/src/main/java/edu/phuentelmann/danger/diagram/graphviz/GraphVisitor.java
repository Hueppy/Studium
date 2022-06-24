package edu.phuentelmann.danger.diagram.graphviz;

public interface GraphVisitor<T> {
    public void visit(Graph g, T t);
    public void visit(Node n, T t);
    public void visit(Edge e, T t);

    public void visit(Graph.Attributes a, T t);
    public void visit(Node.Attributes a, T t);
    public void visit(Edge.Attributes a, T t);
}
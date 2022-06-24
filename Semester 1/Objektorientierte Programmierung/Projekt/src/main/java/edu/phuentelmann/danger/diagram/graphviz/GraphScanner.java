package edu.phuentelmann.danger.diagram.graphviz;

/**
 * Base visitor base, that "scans" through the model
 */
public abstract class GraphScanner<T> implements GraphVisitor<T> {
    public void visit(Graph g, T t) {
        for (Graph.Statement s : g.getStatements()) {
            s.accept(this, t);
        }
    }

    public void visit(Node n, T t) {
        n.getAttributes().accept(this, t);
    }

    public void visit(Edge e, T t) {
        e.getAttributes().accept(this, t);
    }

    public abstract void visit(Graph.Attributes a, T t); 
    public abstract void visit(Node.Attributes a, T t);
    public abstract void visit(Edge.Attributes a, T t);    
}

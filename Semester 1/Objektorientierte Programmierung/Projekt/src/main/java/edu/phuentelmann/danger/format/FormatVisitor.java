package edu.phuentelmann.danger.format;

public interface FormatVisitor {
    void beginVisit(Bold bold);
    void beginVisit(Header header);
    void beginVisit(Italic italic);
    void beginVisit(Link link);
    void beginVisit(Quote quote);
    void beginVisit(UnorderedListItem listItem);
    void endVisit();
    void visit(MonospacedText text);
    void visit(Text text);
}

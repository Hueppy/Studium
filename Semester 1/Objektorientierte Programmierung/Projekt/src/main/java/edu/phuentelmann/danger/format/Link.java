package edu.phuentelmann.danger.format;


import java.util.List;

/**
 * Adds a clickable link to format elements
 */
public class Link extends FormatComposite {
    public Link(List<FormatBase> composites, String target) {
        super(composites);
        this.target = target;
    }

    private String target;

    public String getTarget() {
        return target;
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.beginVisit(this);
        super.accept(visitor);
        visitor.endVisit();
    }
}

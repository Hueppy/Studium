package edu.phuentelmann.danger.format;

import java.util.List;

/**
 * Formats the elements as italic.
 */
public class Italic extends FormatComposite {
    public Italic(List<FormatBase> composites) {
        super(composites);
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.beginVisit(this);
        super.accept(visitor);
        visitor.endVisit();
    }
}

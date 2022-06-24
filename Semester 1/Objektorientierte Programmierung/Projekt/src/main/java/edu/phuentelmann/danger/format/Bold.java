package edu.phuentelmann.danger.format;

import java.util.List;

/**
 * Formats the elements as bold.
 */
public class Bold extends FormatComposite {
    public Bold(List<FormatBase> composites) {
        super(composites);
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.beginVisit(this);
        super.accept(visitor);
        visitor.endVisit();
    }
}

package edu.phuentelmann.danger.format;

import java.util.List;

/**
 * Composite class for each individual list item
 */
public class UnorderedListItem extends FormatComposite {
    public UnorderedListItem(List<FormatBase> composites) {
        super(composites);
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.beginVisit(this);
        super.accept(visitor);
        visitor.endVisit();
    }
}

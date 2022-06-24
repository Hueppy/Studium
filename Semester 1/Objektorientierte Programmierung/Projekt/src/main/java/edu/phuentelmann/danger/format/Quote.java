package edu.phuentelmann.danger.format;

import java.util.List;

/**
 * Formats multiple format elements into one quote.
 */
public class Quote extends FormatComposite {
    public Quote(List<FormatBase> composites) {
        super(composites);
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.beginVisit(this);
        super.accept(visitor);
        visitor.endVisit();
    }
}

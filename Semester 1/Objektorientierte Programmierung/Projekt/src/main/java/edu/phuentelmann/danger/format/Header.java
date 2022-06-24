package edu.phuentelmann.danger.format;

import java.util.List;

/**
 * Formats multiple format elements to one header line with specific level
 */
public class Header extends FormatComposite {
    public Header(List<FormatBase> composites, int level) {
        super(composites);
        this.level = level;
    }

    private int level;

    public int getLevel() {
        return level;
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.beginVisit(this);
        super.accept(visitor);
        visitor.endVisit();
    }
}

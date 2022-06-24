package edu.phuentelmann.danger.format;

import java.util.List;

/**
 * A "blank" format object that composites multiple other format objects
 */
public class FormatCollection extends FormatComposite {
    public FormatCollection(List<FormatBase> composites) {
        super(composites);
    }

    public void add(FormatBase item) {
        getComposites().add(item);
    }
}

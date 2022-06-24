package edu.phuentelmann.danger;

import edu.phuentelmann.danger.format.FormatCollection;
import edu.phuentelmann.danger.format.FormatCompositeBuilder;

/**
 * Builder for a collection of format objects (e.g. a markdown file)
 */
public class FormatCollectionBuilder extends FormatCompositeBuilder {
    public FormatCollectionBuilder() {
        super(FormatCollection::new);
    }
}

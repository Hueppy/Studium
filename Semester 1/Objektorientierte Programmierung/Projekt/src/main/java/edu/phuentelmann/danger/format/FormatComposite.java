package edu.phuentelmann.danger.format;

import java.util.ArrayList;
import java.util.List;

/**
 * Base class for 'composite' type format abstraction.
 * These take a collection of format elements as input
 * and alters the overall appearance of all elements together
 */
public abstract class FormatComposite extends FormatBase {
    public FormatComposite(List<FormatBase> composites) {
        this.composites = composites;
    }

    private List<FormatBase> composites;

    @Override
    public void accept(FormatVisitor visitor) {
        for (FormatBase composite: composites) {
            composite.accept(visitor);
        }
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        FormatComposite clone = (FormatComposite)super.clone();

        clone.composites = new ArrayList<>();
        for (FormatBase composite: composites) {
            clone.composites.add((FormatBase)(composite.clone()));
        }

        return clone;
    }

    protected List<FormatBase> getComposites() {
        return composites;
    }
}

package edu.phuentelmann.danger.format;

/**
 * Base class for format abstraction.
 */
public abstract class FormatBase implements Cloneable {
    public abstract void accept(FormatVisitor visitor);

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}

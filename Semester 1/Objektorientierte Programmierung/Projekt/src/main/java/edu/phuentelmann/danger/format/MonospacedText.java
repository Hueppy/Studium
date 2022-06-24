package edu.phuentelmann.danger.format;

/**
 * Text that is monospaced.
 */
public class MonospacedText extends Text {
    public MonospacedText(String text) {
        super(text);
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.visit(this);
    }
}

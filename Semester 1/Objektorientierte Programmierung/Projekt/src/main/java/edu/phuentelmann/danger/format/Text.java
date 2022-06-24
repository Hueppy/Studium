package edu.phuentelmann.danger.format;

/**
 * Simple text element.
 */
public class Text extends FormatBase {
    public Text(String text) {
        this.text = text;
    }

    private String text;

    public String getText() {
        return text;
    }

    @Override
    public void accept(FormatVisitor visitor) {
        visitor.visit(this);
    }
}

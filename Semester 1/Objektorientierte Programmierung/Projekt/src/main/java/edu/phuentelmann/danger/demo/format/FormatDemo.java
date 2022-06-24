package edu.phuentelmann.danger.demo.format;

import edu.phuentelmann.danger.FormatCollectionBuilder;
import edu.phuentelmann.danger.format.FormatComposite;
import edu.phuentelmann.danger.format.markdown.MarkdownFormatVisitor;

public class FormatDemo {
    public static void main(String[] args) {
        MarkdownFormatVisitor visitor = new MarkdownFormatVisitor();
        FormatCollectionBuilder fcb = new FormatCollectionBuilder();
        FormatComposite fc = fcb
                .addHeader(1, (x) -> x.addText("Hello World!"))
                .addListItem((x) -> x.addText("Simple list item"))
                .addListItem((x) -> x.addItalic((y) -> y.addText("Another more complex list item")))
                .addBold((x) -> x.addLink("https://gitlab.com/phuentelmann/danger", (y) -> y.addText("Formatted Text")))
                .build();

        fc.accept(visitor);
        System.out.println(visitor.getResult());
    }
}

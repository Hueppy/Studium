package edu.phuentelmann.danger;

import edu.phuentelmann.danger.diagram.graphviz.GraphVizInvoker;
import edu.phuentelmann.danger.diagram.graphviz.UmlGraphBuilder;
import edu.phuentelmann.danger.format.markdown.MarkdownFormatVisitor;

import java.util.List;

/**
 * Sample doclet implementation.
 * Generates a markdown documentation of the elements and an UML "like" class diagram.
 */
public class BasicDoclet extends BaseDoclet {
    @Override
    protected DocumentationAction getAction() {
        return new DocumentationActionComposite(
                List.of(
                    new MarkdownAction(FormatCollectionBuilder::new, MarkdownFormatVisitor::new),
                    new UmlAction(UmlGraphBuilder::new, GraphVizInvoker::new)
                ));
    }
}

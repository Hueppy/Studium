package edu.phuentelmann.danger;

import javax.lang.model.element.Element;
import java.util.List;
import java.util.Set;

/**
 * Action that composites multiple actions.
 * Can be used to chain multiple actions.
 */
public class DocumentationActionComposite implements DocumentationAction {
    public DocumentationActionComposite(List<DocumentationAction> actions) {
        this.actions = actions;
    }

    private final List<DocumentationAction> actions;

    @Override
    public void document(Set<? extends Element> elements, String destinationDir) {
        for (DocumentationAction action : actions) {
            action.document(elements, destinationDir);
        }
    }
}

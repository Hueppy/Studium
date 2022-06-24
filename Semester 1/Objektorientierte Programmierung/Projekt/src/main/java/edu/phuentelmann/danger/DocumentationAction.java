package edu.phuentelmann.danger;

import javax.lang.model.element.Element;
import java.util.Set;

/**
 * Interface for documentation action.
 * An action performs some action on the supplied elements and outputs its result in the destination directory.
 */
public interface DocumentationAction {
    void document(
            Set<? extends Element> elements,
            String destinationDir);

}

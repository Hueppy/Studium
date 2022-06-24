package edu.phuentelmann.danger;

import jdk.javadoc.doclet.*;
import javax.lang.model.SourceVersion;

/**
 * Base for custom doclets
 */
public abstract class BaseDoclet extends StandardDoclet {
    protected abstract DocumentationAction getAction();
    protected String getDestinationDirectory() {
        return "build/docs/";
    }

    @Override
    public String getName() {
        return getClass().getSimpleName();
    }

    @Override
    public SourceVersion getSupportedSourceVersion() {
        return SourceVersion.latest();
    }

    @Override
    public boolean run(DocletEnvironment environment) {
        getAction().document(environment.getSpecifiedElements(), getDestinationDirectory());
        return true;
    }
}

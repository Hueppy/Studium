package edu.phuentelmann.danger.utils;

import javax.lang.model.type.*;
import javax.lang.model.util.SimpleTypeVisitor14;

/**
 * Gets the "raw" type name of an element
 */
// it's fckng raw
public class RawTypeNameVisitor extends SimpleTypeVisitor14<String, Object> {
    @Override
    protected String defaultAction(TypeMirror e, Object o) {
        return e.toString()
                .replaceFirst("[a-z.]*", "")
                .replaceAll("<.*>", "");
    }

    @Override
    public String visitArray(ArrayType t, Object o) {
        return visit(t.getComponentType());
    }

    @Override
    public String visitDeclared(DeclaredType t, Object o) {
        final String name = super.visitDeclared(t, o);
        final String enclosingName = visit(t.getEnclosingType());

        if (enclosingName.isBlank()) {
            return name;
        } else {
            return "%s.%s".formatted(enclosingName, name);
        }
    }

    @Override
    public String visitNoType(NoType t, Object o) {
        return "";
    }

    @Override
    public String visitPrimitive(PrimitiveType t, Object o) {
        return t.toString();
    }
}

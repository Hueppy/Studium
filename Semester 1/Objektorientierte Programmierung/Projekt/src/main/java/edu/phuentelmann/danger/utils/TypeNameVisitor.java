package edu.phuentelmann.danger.utils;

import javax.lang.model.type.*;
import javax.lang.model.util.SimpleTypeVisitor14;

/**
 * Gets the "normalized" type name of an element
 */
public class TypeNameVisitor extends SimpleTypeVisitor14<String, Object> {
    private static final TypeVisitor<String, Object> rawVisitor = new RawTypeNameVisitor();

    @Override
    protected String defaultAction(TypeMirror e, Object o) {
        return rawVisitor.visit(e);
    }

    @Override
    public String visitArray(ArrayType t, Object o) {
        return super.visitArray(t, o) + "[]";
    }

    @Override
    public String visitDeclared(DeclaredType t, Object o) {
        final String rawName = super.visitDeclared(t, o);
        final String typeArgs = t.getTypeArguments().stream()
                .map((x) -> visit(x))
                .reduce((x, y) -> "%s, %s".formatted(x, y))
                .orElse("");

        if (typeArgs.isBlank()) {
            return rawName;
        } else {
            return "%s<%s>".formatted(rawName, typeArgs);
        }
    }

    @Override
    public String visitNoType(NoType t, Object o) {
        return "void";
    }
}

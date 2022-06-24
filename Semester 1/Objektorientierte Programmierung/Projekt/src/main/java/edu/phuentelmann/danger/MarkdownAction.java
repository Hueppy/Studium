package edu.phuentelmann.danger;

import edu.phuentelmann.danger.format.*;
import edu.phuentelmann.danger.format.markdown.*;
import edu.phuentelmann.danger.utils.Lazy;
import edu.phuentelmann.danger.utils.RawTypeNameVisitor;

import javax.lang.model.element.*;
import javax.lang.model.type.*;
import javax.lang.model.util.ElementScanner14;
import javax.lang.model.util.SimpleTypeVisitor14;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Path;
import java.util.*;
import java.util.function.BiConsumer;
import java.util.function.Function;
import java.util.function.Supplier;

/**
 * Documenation action that generates markdown documents for the supplied elements.
 */
public class MarkdownAction implements DocumentationAction {
    /**
     * Data base for internal visitor
     */
    protected abstract class MarkdownElementVisitorData {
        public MarkdownElementVisitorData(
                FormatCompositeBuilder builder,
                Function<TypeElement, String> fileResolver,
                Function<TypeElement, MarkdownElementVisitorData> subDataFactory) {
            this.fileResolver = fileResolver;
            this.subDataFactory = subDataFactory;
            subData = new ArrayList<>();
            info = builder.addSubCollection();
            types = new Lazy<>(() -> createTypes(builder));
            executables = new Lazy<>(() -> createExecutables(builder));
            fields = new Lazy<>(() -> createFields(builder));
        }

        protected final TypeVisitor<Object, FormatCompositeBuilder> typeNameVisitor = new SimpleTypeVisitor14<>() {
            final TypeVisitor<String, Object> strTypeNameVisitor = new RawTypeNameVisitor();

            @Override
            protected Object defaultAction(TypeMirror e, FormatCompositeBuilder b) {
                b.addText(e.accept(strTypeNameVisitor, null).replaceAll("<.*>", ""));
                return super.defaultAction(e, b);
            }

            @Override
            public Object visitArray(ArrayType t, FormatCompositeBuilder b) {
                t.getComponentType().accept(this, b);
                b.addText("[]");
                return null;
            }

            @Override
            public Object visitDeclared(DeclaredType t, FormatCompositeBuilder b) {
                b.addLink(
                        fileResolver.apply((TypeElement)t.asElement()),
                        (l) -> super.visitDeclared(t, l));

                if (!t.getTypeArguments().isEmpty()) {
                    b.addText("<");
                    boolean first = true;
                    for (TypeMirror inner : t.getTypeArguments()) {
                        if (!first) {
                            b.addText(", ");
                        }

                        inner.accept(this, b);

                        first = false;
                    }
                    b.addText(">");
                }
                return null;
            }
        };

        protected final FormatCompositeBuilder info;
        protected final Lazy<FormatCompositeBuilder> types;
        protected final Lazy<FormatCompositeBuilder> executables;
        protected final Lazy<FormatCompositeBuilder> fields;
        protected final Function<TypeElement, String> fileResolver;
        protected final Function<TypeElement, MarkdownElementVisitorData> subDataFactory;
        protected final List<MarkdownElementVisitorData> subData;

        protected FormatCompositeBuilder createTypes(FormatCompositeBuilder builder) {
            return builder.addSubCollection();
        }

        protected FormatCompositeBuilder createExecutables(FormatCompositeBuilder builder) {
            return builder.addSubCollection();
        }

        protected FormatCompositeBuilder createFields(FormatCompositeBuilder builder) {
            return builder.addSubCollection();
        }

        public abstract void initWithType(TypeElement e);

        public abstract MarkdownElementVisitorData addType(TypeElement e);
        public abstract MarkdownElementVisitorData addExecutable(ExecutableElement e);
        public abstract MarkdownElementVisitorData addField(VariableElement e);
    }

    /**
     * Default implemenation of visitor data
     */
    private class DefaultMarkdownElementVisitorData extends MarkdownElementVisitorData {
        public DefaultMarkdownElementVisitorData(
                FormatCompositeBuilder builder,
                Function<TypeElement, String> fileResolver,
                Function<TypeElement, MarkdownElementVisitorData> subDataFactory) {
            super(builder, fileResolver, subDataFactory);
        }

        private String typeName;

        @Override
        protected FormatCompositeBuilder createExecutables(FormatCompositeBuilder builder) {
            final FormatCompositeBuilder executables = super.createExecutables(builder);
            executables.addHeader(2, (h) -> h.addText("Methods"));

            return executables;
        }

        @Override
        protected FormatCompositeBuilder createTypes(FormatCompositeBuilder builder) {
            final FormatCompositeBuilder types = super.createTypes(builder);
            types.addHeader(2, (h) -> h.addText("Types"));

            return types;
        }

        @Override
        protected FormatCompositeBuilder createFields(FormatCompositeBuilder builder) {
            final FormatCompositeBuilder fields = super.createFields(builder);
            fields.addHeader(2, (h) -> h.addText("Fields"));

            return fields;
        }

        @Override
        public void initWithType(TypeElement e) {
            final BiConsumer<TypeMirror, FormatCompositeBuilder> inheritanceBuilder = new BiConsumer<TypeMirror, FormatCompositeBuilder>() {
                final TypeVisitor<Object, FormatCompositeBuilder> inheritanceTypeNameVisitor = new SimpleTypeVisitor14<>() {
                    @Override
                    protected Object defaultAction(TypeMirror e, FormatCompositeBuilder b) {
                        return e.accept(typeNameVisitor, b);
                    }

                    @Override
                    public Object visitDeclared(DeclaredType t, FormatCompositeBuilder b) {
                        super.visitDeclared(t, b);

                        final Element e = t.asElement();
                        if (e instanceof TypeElement) {
                            accept(((TypeElement) e).getSuperclass(), b);
                        }

                        return null;
                    }
                };

                @Override
                public void accept(TypeMirror t, FormatCompositeBuilder b) {
                    if (t != null && t.getKind() != TypeKind.NONE) {
                        b.addText(" -> ");
                        t.accept(inheritanceTypeNameVisitor, b);
                    }
                }
            };

            typeName = e.getSimpleName().toString();
            info.addHeader(1, (h) -> {
                h.addText(typeName);
                final List<? extends TypeMirror> interfaces = e.getInterfaces();
                boolean first = true;
                if (!interfaces.isEmpty()) {
                    h.addText("(");
                    for (TypeMirror i: interfaces) {
                        if (!first) {
                            h.addText(", ");
                        }
                        i.accept(typeNameVisitor, h);
                        first = false;
                    }
                    h.addText(")");
                }
            });
            info.addBold((b) -> inheritanceBuilder.accept(e.getSuperclass(), b));

            for (AnnotationMirror a: e.getAnnotationMirrors()) {
                info.addText(a.toString());
            }
        }

        private void addModifier(Set<Modifier> modifier, FormatCompositeBuilder b) {
            if (!modifier.isEmpty()) {
                b.addText(modifier.stream()
                    .map((m) -> m.toString())
                    .reduce((l, r) -> "%s %s".formatted(l, r))
                    .orElse(""));
                b.addText(" ");
            }
        }

        @Override
        public MarkdownElementVisitorData addType(TypeElement e) {
            final MarkdownElementVisitorData subData = subDataFactory.apply(e);
            types.get().addListItem((b) -> {
                addModifier(e.getModifiers(), b);
                e.asType().accept(typeNameVisitor, b);
            });
            return subData;
        }

        @Override
        public MarkdownElementVisitorData addExecutable(ExecutableElement e) {
            executables.get().addListItem((b) -> {
                addModifier(e.getModifiers(), b);

                final String name = e.getSimpleName().toString();

                if (name.equals("<init>")) {
                    b.addText(typeName);
                } else {
                    e.getReturnType().accept(typeNameVisitor, b);
                    b.addText(" ");
                    b.addText(name);
                }

                boolean first = true;
                b.addText("(");
                for (VariableElement p: e.getParameters()) {
                    if (!first) {
                        b.addText(", ");
                    }
                    addModifier(p.getModifiers(), b);
                    p.asType().accept(typeNameVisitor, b);
                    b.addText(" ");
                    b.addText(p.getSimpleName().toString());
                    first = false;
                }
                b.addText(");");
            });
            return this;
        }

        @Override
        public MarkdownElementVisitorData addField(VariableElement e) {
            fields.get().addListItem((b) -> {
                addModifier(e.getModifiers(), b);
                e.asType().accept(typeNameVisitor, b);
                b.addText(" ");
                b.addText(e.getSimpleName().toString());
            });

            return this;
        }
    }

    /**
     * Visitor that converts the visited elements to a format model using its supplied data class
     */
    protected class MarkdownElementVisitor extends ElementScanner14<Object, MarkdownElementVisitorData> {
        @Override
        public Object visitExecutable(ExecutableElement e, MarkdownElementVisitorData data) {
            data.addExecutable(e);
            return null;
        }

        @Override
        public Object visitType(TypeElement e, MarkdownElementVisitorData data) {
            return super.visitType(e, data.addType(e));
        }

        @Override
        public Object visitVariable(VariableElement e, MarkdownElementVisitorData data) {
            return super.visitVariable(e, data.addField(e));
        }
    }

    public MarkdownAction(
            Supplier<FormatCollectionBuilder> formatBuilderfactory,
            Supplier<MarkdownFormatVisitor> visitorFactory) {
        this.formatBuilderfactory = formatBuilderfactory;
        this.visitorFactory = visitorFactory;
    }

    private Supplier<FormatCollectionBuilder> formatBuilderfactory;
    private Supplier<MarkdownFormatVisitor> visitorFactory;

    @Override
    public void document(Set<? extends Element> elements, String destinationDir) {
        final Map<TypeElement, FormatCollectionBuilder> files = new HashMap<>();
        final Function<TypeElement, String> fileResolver = (e) -> {
            if (e == null) {
                return "home";
            }

            final String name = e.getQualifiedName().toString().replaceAll("(<|>)", "");

            if (name.startsWith("java") || name.startsWith("jdk")) {
                return "https://docs.oracle.com/javase/9/docs/api/%s.html".formatted(name.replaceAll("\\.", "/"));
            }

            return name;
        };

        final Function<TypeElement, MarkdownElementVisitorData> dataFactory = new Function<TypeElement, MarkdownElementVisitorData>() {
            @Override
            public MarkdownElementVisitorData apply(TypeElement e) {
                final FormatCollectionBuilder fcb = formatBuilderfactory.get();
                final MarkdownElementVisitorData data = new DefaultMarkdownElementVisitorData(fcb, fileResolver, this);
                files.put(e, fcb);
                if (e != null) {
                    data.initWithType(e);
                }
                return data;
            }
        };

        final MarkdownElementVisitorData rootData = dataFactory.apply(null);

        for (Element e: elements) {
            e.accept(new MarkdownElementVisitor(), rootData);
        }

        for (Map.Entry<TypeElement, FormatCollectionBuilder> file: files.entrySet()) {
            try {
                final String name = fileResolver.apply(file.getKey()) + ".md";
                final FileOutputStream fs = new FileOutputStream(Path.of(destinationDir, name).toString());
                final MarkdownFormatVisitor visitor = visitorFactory.get();
                file.getValue().build().accept(visitor);
                fs.write(visitor.getResult().getBytes());
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

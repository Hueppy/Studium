package edu.phuentelmann.danger;

import java.io.FileOutputStream;
import java.io.PrintStream;
import java.nio.file.Paths;
import java.util.Set;
import java.util.function.Consumer;
import java.util.function.Supplier;

import javax.lang.model.util.ElementScanner14;
import javax.lang.model.element.*;
import javax.lang.model.type.*;

import edu.phuentelmann.danger.diagram.graphviz.*;
import edu.phuentelmann.danger.diagram.graphviz.UmlGraphBuilder.*;
import edu.phuentelmann.danger.diagram.graphviz.UmlGraphBuilder.ClassBuilder.*;
import edu.phuentelmann.danger.diagram.graphviz.UmlGraphBuilder.RelationshipBuilder.Type;
import edu.phuentelmann.danger.utils.RawTypeNameVisitor;
import edu.phuentelmann.danger.utils.TypeNameVisitor;

/**
 * Documentation action that generates an UML class diagram like graph from the supplied elements
 */
public class UmlAction implements DocumentationAction {
    /**
     * Base class for visitor data
     */
    private static abstract class UmlElementVisitorData {
        public UmlElementVisitorData(UmlGraphBuilder b) {
            this.b = b;
        }

        protected final UmlGraphBuilder b;

        public void addClass(TypeElement e, Consumer<UmlElementVisitorData> chain) {
            b.addClass(typeNameVisitor.visit(e.asType()), (c) -> {
                final UmlClassElementVisitorData data = new UmlClassElementVisitorData(b, c);

                data.addRelation(Type.Inheritance, e.getSuperclass());
                for (TypeMirror i : e.getInterfaces()) {
                    data.addRelation(Type.Implementation, i);
                }

                chain.accept(data);
            });
        }

        public abstract void addField(VariableElement e);
        public abstract void addMethod(ExecutableElement e);

    }

    /**
     * Visitor data for a class "parent" element
     */
    private static class UmlClassElementVisitorData extends UmlElementVisitorData {
        public UmlClassElementVisitorData(UmlGraphBuilder b, ClassBuilder c) {
            super(b);
            this.c = c;
        }

        private final ClassBuilder c;
        private final RawTypeNameVisitor rawTypeNameVisitor = new RawTypeNameVisitor();

        private Visibility getVisibility(Set<Modifier> modifier) {
            final Modifier v = modifier.stream().filter(
                    (m) -> m.ordinal() >= Modifier.PUBLIC.ordinal() && m.ordinal() <= Modifier.PRIVATE.ordinal())
                    .findAny().orElse(Modifier.PUBLIC);

            return switch (v) {
                case PRIVATE -> Visibility.Private;
                case PROTECTED -> Visibility.Protected;
                default -> Visibility.Public;
            };
        }

        protected void addRelation(Type relationType, TypeMirror type) {
            final String rawName = rawTypeNameVisitor.visit(type);

            if (type.toString().startsWith("edu.phuentelmann.danger")
                    && !c.getName().equals(rawName)) { // TODO: remove hack
                b.addRelationship(relationType, c.getName(), typeNameVisitor.visit(type));
            }
        }

        @Override
        public void addField(VariableElement e) {
            final String type = typeNameVisitor.visit(e.asType());

            c.addField(getVisibility(e.getModifiers()), e.getSimpleName().toString(), type);
            addRelation(Type.Aggregation, e.asType());
        }

        @Override
        public void addMethod(ExecutableElement e) {
            String n = e.getSimpleName().toString();
            if (n.equals("<init>")) {
                n = c.getName();
            }
            c.addMethod(getVisibility(e.getModifiers()), n, typeNameVisitor.visit(e.getReturnType()), (m) -> {
                for (VariableElement parameter : e.getParameters()) {
                    m.addParameter(parameter.getSimpleName().toString(),
                            typeNameVisitor.visit(parameter.asType()));

                    addRelation(Type.Association, parameter.asType());
                }
            });
            addRelation(Type.Association, e.getReturnType());
        }
    }

    public UmlAction(
            Supplier<UmlGraphBuilder> builderFactory,
            Supplier<GraphVizInvoker> invokerFactory) {
        this.builderFactory = builderFactory;
        this.invokerFactory = invokerFactory;
    }

    private static final TypeVisitor<String, Object> typeNameVisitor = new TypeNameVisitor();
    private static final ElementVisitor<Object, UmlElementVisitorData> visitor = new ElementScanner14<>() {
        public Object visitVariable(VariableElement e, UmlElementVisitorData p) {
            p.addField(e);
            return null;
        }

        public Object visitExecutable(ExecutableElement e, UmlElementVisitorData p) {
            p.addMethod(e);
            return null;
        }

        public Object visitType(TypeElement e, UmlElementVisitorData p) {
            p.addClass(e, (d) -> super.visitType(e, d));
            return null;
        }
    };

    private final Supplier<UmlGraphBuilder> builderFactory;
    private final Supplier<GraphVizInvoker> invokerFactory;

    private void saveGraph(Graph g, String path) {
        final GraphVizInvoker invoker = invokerFactory.get();

        try {
            invoker.invoke((in) -> {
                final DotGraphVisitor dotVisitor = new DotGraphVisitor();
                g.accept(dotVisitor, new PrintStream(in, true));
                //g.accept(dotVisitor, System.out);
            }, (out, err) -> {
                if (err.available() > 0) {
                    System.err.write(err.readAllBytes());
                }
                if (out.available() > 0) {
                    try (FileOutputStream fs = new FileOutputStream(path)) {
                        fs.write(out.readAllBytes());
                        System.out.println("Diagram saved");
                    }
                }
                else {
                    System.out.println("Nothing done :(");
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void document(Set<? extends Element> elements, String destinationDir) {
        final UmlGraphBuilder b = builderFactory.get();
        final UmlElementVisitorData baseData = new UmlElementVisitorData(b) {
            @Override
            public void addField(VariableElement e) {
            }

            @Override
            public void addMethod(ExecutableElement e) {
            }
        };

        for (Element element : elements) {
            element.accept(visitor, baseData);
        }

        saveGraph(b.build(), Paths.get(destinationDir,"diag.svg").toString());
        saveGraph(b.buildSimple(), Paths.get(destinationDir,"simple_diag.svg").toString());
    }
    
}

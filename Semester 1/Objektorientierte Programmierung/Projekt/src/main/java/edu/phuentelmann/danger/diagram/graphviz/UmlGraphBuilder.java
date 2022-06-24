package edu.phuentelmann.danger.diagram.graphviz;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

import edu.phuentelmann.danger.diagram.graphviz.Edge.Attributes.Arrow;
import edu.phuentelmann.danger.diagram.graphviz.Edge.Attributes.Arrow.Side;
import edu.phuentelmann.danger.diagram.graphviz.Edge.Attributes.Direction;
import edu.phuentelmann.danger.diagram.graphviz.Edge.Attributes.Style;
import edu.phuentelmann.danger.diagram.graphviz.Graph.Attributes.RankDirection;
import edu.phuentelmann.danger.diagram.graphviz.Graph.Type;
import edu.phuentelmann.danger.diagram.graphviz.Node.Attributes.Shape;

/**
 * Builder class for generation UML class diagram like graphs
 */
public class UmlGraphBuilder {
    public static class ClassBuilder {
        public static enum Visibility {
            Public,
            Private,
            Protected,
            Package;

            public String getVisibility() {
                switch (this) {
                    case Public:    return "+";
                    case Private:   return "-";
                    case Protected: return "#";
                    case Package:   return "~";
                    default:        return " ";
                }
            }
        }

        public static class VariableBuilder {
            public VariableBuilder(String name, String type) {
                this.name = name;
                this.type = type;
            }

            private final String name;
            private final String type;

            public String build() {
                return "%s : %s".formatted(name, type);
            }

            public String getName() {
                return name;
            }

            public String getType() {
                return type;
            }
        }

        public static class FieldBuilder extends VariableBuilder {
            public FieldBuilder(Visibility visibility, String name, String type) {
                super(name, type);
                this.visibility = visibility;
            }

            private final Visibility visibility;

            @Override
            public String build() {
                return "%s %s\\l".formatted(visibility.getVisibility(), super.build());
            }
        }

        public static class MethodBuilder {
            public MethodBuilder(Visibility visibility, String name, String type) {
                this.visibility = visibility;
                this.name = name;
                this.type = type;
                this.parameter = new ArrayList<>();
            }

            private final Visibility visibility;
            private final String name;
            private final String type;
            private final List<VariableBuilder> parameter;

            public void addParameter(String name, String type) {
                parameter.add(new VariableBuilder(name, type));
            }

            public List<VariableBuilder> getParameter() {
                return parameter;
            }
         
            public String build() {
                return "%s %s(%s) : %s\\l".formatted(
                    visibility.getVisibility(), 
                    name, 
                    this.parameter.stream()
                        .map((x) -> x.build())
                        .reduce((x, y) -> "%s, %s".formatted(x, y))
                        .orElse(""),
                    type);
            }
        }

        public ClassBuilder(String name) {
            this.name = name;
            this.fields = new ArrayList<>();
            this.methods = new ArrayList<>();
            this.relationships = new ArrayList<>();
        }

        private final String name;
        private final List<FieldBuilder> fields;
        private final List<MethodBuilder> methods;
        private final List<RelationshipBuilder> relationships;

        public ClassBuilder addField(
                Visibility visibility,
                String name,
                String type) {
            fields.add(new FieldBuilder(visibility, name, type));
            return this;
        }

        public ClassBuilder addMethod(
                Visibility visibility,
                String name,
                String type,
                Consumer<MethodBuilder> initializer) {
            final MethodBuilder b = new MethodBuilder(visibility, name, type);
            methods.add(b);
            initializer.accept(b);
            return this;
        }

        public void build(Graph g) {
            g.addNode(name.replaceFirst("<.*>", "")).getAttributes().setLabel("{%s|%s|%s}".formatted(
                name,
                fields.stream()
                    .map((x) -> x.build())
                    .reduce((x, y) -> x + y)
                    .orElse(""),
                methods.stream()
                    .map((x) -> x.build())
                    .reduce((x, y) -> x + y)
                    .orElse("")
            ));
        }

        public void buildSimple(Graph g) {
            g.addNode(name.replaceFirst("<.*>", "")).getAttributes().setLabel(name);
        }

        public String getName() {
            return name;
        }
    }

    public static class RelationshipBuilder {
        public static enum Type {
            Inheritance,
            Implementation,
            Aggregation,
            Composition,
            Association,
            BidiAssociation;

            public void build(Edge.Attributes a) {
                switch (this) {
                    case Inheritance:
                        a.setDirection(Direction.Forward);
                        a.getHead().setModifier(new Arrow.Modifier(true, Side.None));
                        a.getHead().setShape(Arrow.Shape.Normal);
                        a.setStyle(Style.Solid);
                        break;
                    case Implementation:
                        a.setDirection(Direction.Forward);
                        a.getHead().setModifier(new Arrow.Modifier(true, Side.None));
                        a.getHead().setShape(Arrow.Shape.Normal);
                        a.setStyle(Style.Dashed);
                        break;
                    case Aggregation:
                        a.setDirection(Direction.Back);
                        a.getTail().setModifier(new Arrow.Modifier(true, Side.None));
                        a.getTail().setShape(Arrow.Shape.Diamond);
                        a.setStyle(Style.Solid);
                        break;
                    case Composition:
                        a.setDirection(Direction.Back);
                        a.getTail().setModifier(new Arrow.Modifier(false, Side.None));
                        a.getTail().setShape(Arrow.Shape.Diamond);
                        a.setStyle(Style.Solid);
                        break;
                    case Association:
                        a.setDirection(Direction.Forward);
                        a.getHead().setModifier(new Arrow.Modifier(false, Side.None));
                        a.getHead().setShape(Arrow.Shape.Vee);
                        a.setStyle(Style.Solid);
                        break;
                    case BidiAssociation:
                        Association.build(a);
                        a.setDirection(Direction.Both);
                        a.getTail().setModifier(new Arrow.Modifier(false, Side.None));
                        a.getTail().setShape(Arrow.Shape.Vee);
                        break;

                    default:
                        break;
                }
            }
        }

        public RelationshipBuilder(Type type, String source, String target) {
            this.type = type;
            this.source = source;
            this.target = target;
        }

        private Type type;
        private final String source;
        private final String target;

        public void build(Graph g) {
            final Edge e = g.addEdge(source.replaceFirst("<.*>", ""), target.replaceFirst("<.*>", ""));
            type.build(e.getAttributes());
        }

        public Type getType() {
            return type;
        }

        public void setType(Type t) {
            type = t;
        }

        public String getSource() {
            return source;
        }

        public String getTarget() {
            return target;
        }
    }

    public UmlGraphBuilder() {
        classes = new ArrayList<>();
        relationships = new ArrayList<>();
    }

    private final List<ClassBuilder> classes;
    private final List<RelationshipBuilder> relationships;

    public UmlGraphBuilder addClass(String name, Consumer<ClassBuilder> initializer) {
        if (!classes.stream().anyMatch((x) -> x.name.equals(name))) {
            final ClassBuilder c = new ClassBuilder(name);
            classes.add(c);
            initializer.accept(c);
        }
        return this;
    }

    private RelationshipBuilder findRelationship(String source, String target) {
        return relationships.stream()
                .filter((x) -> x.getSource().equals(source)
                        && x.getTarget().equals(target))
                .findFirst()
                .orElse(null);

    }

    public UmlGraphBuilder addRelationship(
            RelationshipBuilder.Type type,
            String source,
            String target
    ) {
        if (!target.equals(source)) {
            final RelationshipBuilder existing = findRelationship(source, target);

            if (existing == null) {
                relationships.add(new RelationshipBuilder(type, source, target));
            } else if (existing.type.ordinal() > type.ordinal()) {
                existing.setType(type);
            }
        }
        return this;
    }

    private Graph createGraph(Shape nodeShape) {
        final String fontName = "Bitstream Vera Sans";
        final Graph g = new Graph(Type.Directed);

        final Graph.Attributes ga = g.changeAttributes();
        ga.setFontName(fontName);
        ga.setFontSize(25);
        ga.setRankDir(RankDirection.BottomTop);
        ga.setSplines(Graph.Attributes.Splines.Ortho);
        ga.setNodesep(1);
        ga.setRanksep(2);

        final Node.Attributes na = g.changeNodeAttributes();
        na.setFontName(fontName);
        na.setFontSize(25);
        na.setShape(nodeShape);

        return g;
    }

    private void buildRelationships(Graph g) {
        final List<RelationshipBuilder> handled = new ArrayList<>();

        for (RelationshipBuilder r : relationships) {
            if (!handled.contains(r)) {
                final RelationshipBuilder reverse = findRelationship(r.getTarget(), r.getSource());
                if (r.getType() != RelationshipBuilder.Type.Association || reverse == null || reverse.getType() != RelationshipBuilder.Type.Association) {
                    r.build(g);
                } else {
                    new RelationshipBuilder(RelationshipBuilder.Type.BidiAssociation, r.getSource(), r.getTarget()).build(g);
                    handled.add(reverse);
                }
                handled.add(r);
            }
        }
    }

    public Graph build() {
        final Graph g = createGraph(Shape.Record);

        for (ClassBuilder c : classes) {
            c.build(g);
        }
        buildRelationships(g);

        return g;
    }

    public Graph buildSimple() {
        final Graph g = createGraph(Shape.Box);
        g.changeNodeAttributes().setWidth(2.5);
        g.changeNodeAttributes().setHeight(1);

        for (ClassBuilder c : classes) {
            c.buildSimple(g);
        }
        buildRelationships(g);

        return g;
    }
}

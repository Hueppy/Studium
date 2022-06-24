package edu.phuentelmann.danger.diagram.graphviz;

import java.awt.Color; // <- why tf is a color class only available in awt?

/**
 * Connection between Nodes in a Graph
 */
public class Edge extends Graph.Statement {
    /**
     * Attributes of Edge
     */
    public static class Attributes extends Graph.Statement {
        /**
         * The type of arrow of an edge.
         * Different combinations are possible (e.g. open diamond arrow).
         * Checkout https://graphviz.org/doc/info/arrows.html
         */
        public static class Arrow implements Cloneable {
            public enum Side {
                None(""),
                Left("l"),
                Right("r");

                Side(String name) {
                    this.name = name;
                }

                private String name;

                @Override
                public String toString() {
                    return name;
                }
            }

            public static class Modifier implements Cloneable {
                public Modifier(boolean open, Side side) {
                    this.open = open;
                    this.side = side;
                }

                private boolean open;
                private Side side;

                @Override
                public boolean equals(Object obj) {
                    if (obj instanceof Modifier) {
                        final Modifier other = (Modifier)obj;
                        return open == other.open
                            && side == other.side;
                    }

                    return super.equals(obj);
                }

                @Override
                protected Object clone() throws CloneNotSupportedException {
                    Modifier clone = (Modifier)super.clone();
                    clone.open = open;
                    clone.side = side;
                    return clone;
                }

                @Override
                public String toString() {
                    return (open ? "o" : "") + 
                        side.toString();
                }
            }

            public enum Shape {
                Box("box"),
                Crow("crow"),
                Curve("curve"),
                ICurve("icurve"),
                Diamond("diamond"),
                Dot("dot"),
                Inv("inv"),
                None("none"),
                Normal("normal"),
                Tee("tee"),
                Vee("vee");

                Shape(String name) {
                    this.name = name;
                }

                private String name;

                @Override
                public String toString() {
                    return name;
                }
            }

            public Arrow() {
                modifier = new Modifier(false, Side.None);
                shape = Shape.Normal;
            }

            private Modifier modifier;
            private Shape shape;
            private Arrow child;

            public Arrow getChild() {
                if (child == null) {
                    child = new Arrow();
                }

                return child;
            }

            @Override
            public boolean equals(Object obj) {
                if (obj instanceof Arrow) {
                    final Arrow other = (Arrow)obj;
                    return modifier.equals(other.modifier)
                        && shape == other.shape;
                }

                return super.equals(obj);
            }

            @Override
            protected Object clone() throws CloneNotSupportedException {
                Arrow clone = (Arrow)super.clone();
                clone.modifier = (Modifier)modifier.clone();
                clone.shape = shape;
                if (child != null)
                    clone.child = (Arrow)child.clone();
                return clone;
            }

            @Override
            public String toString() {
                return modifier.toString() + shape.toString() +
                        (child != null ? child.toString() : "");
            }

            public Modifier getModifier() {
                return modifier;
            }

            public void setModifier(Modifier m) {
                modifier = m;
            }

            public Shape getShape() {
                return shape;
            }

            public void setShape(Shape s) {
                shape = s;
            }
        }

        /**
         * Style of arrow (Solid or Dashed)
         */
        public enum Style {
            Solid,
            Dashed;

            public String toString() {
                return name().toLowerCase();
            }
        }

        /** 
         * Direction of arrow.
         * Forwards points to the target, Back to the source
         */
        public enum Direction {
            Forward,
            Back,
            Both,
            None;

            @Override
            public String toString() {
                return name().toLowerCase();
            }
        }

        private Attributes() {
            color = Color.BLACK;
            head = new Arrow();
            tail = new Arrow();
            style = Style.Solid;
            dir = Direction.Forward;
        }

        private Attributes(Attributes parent) throws CloneNotSupportedException {
            this.parent = parent;
            this.color = parent.color;
            this.style = parent.style;
            this.head = (Arrow)parent.head.clone();
            this.tail = (Arrow)parent.tail.clone();
            this.dir = parent.dir;
        }

        public static final Attributes DEFAULT = new Attributes();

        private Attributes parent;

        private Color color;
        private Arrow head;
        private Arrow tail;
        private Style style;
        private Direction dir;

        public Attributes createChild() {
            try {
                return new Attributes(this);
            } catch (CloneNotSupportedException e) {
                // should never happen
                return null;
            }
        }

        public <T> void accept(GraphVisitor<T> visitor, T t) {
            visitor.visit(this, t);
        }

        public Attributes getParent() {
            return parent;
        }

        public Color getColor() {
            return color;
        }

        public void setColor(Color c) {
            color = c;
        }

        public Style getStyle() {
            return style;
        }

        public void setStyle(Style s) {
            style = s;
        }

        public Arrow getHead() {
            return head;
        }

        public Arrow getTail() {
            return tail;
        }

        public Direction getDirection() {
            return dir;
        }

        public void setDirection(Direction dir) {
            this.dir = dir;
        }
    }

    public Edge(String source, String target, Attributes attributes) {
        this.source = source;
        this.target = target;
        this.attributes = attributes;
    }

    private String source;
    private String target;
    private Attributes attributes;

    public <T> void accept(GraphVisitor<T> visitor, T t) {
        visitor.visit(this, t);
    }

    public Attributes getAttributes() {
        return attributes;
    }

    public String getSource() {
        return source;
    }

    public String getTarget() {
        return target;
    }
}

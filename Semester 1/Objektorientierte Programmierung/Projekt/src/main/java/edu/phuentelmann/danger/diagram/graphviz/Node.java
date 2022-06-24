package edu.phuentelmann.danger.diagram.graphviz;

import java.awt.*;

/**
 * A Node respresents an entity in the graph model.
 */
public class Node extends Graph.Statement {
    /**
     * Attributes of a node
     */
    public static class Attributes extends Graph.Statement {
        public enum Shape {
            Box,
            Ellipse,
            Record;

            @Override
            public String toString() {
                return name().toLowerCase();
            }
        }

        private Attributes() {
            color = Color.BLACK;
            label = "\n";
            shape = Shape.Ellipse;
            fontSize = 14.0;
            fontName = "";
            width = 0.75;
            height = 0.5;
        }

        private Attributes(Attributes parent) {
            this.parent = parent;
            color = parent.color;
            label = parent.label;
            shape = parent.shape;
            fontSize = parent.fontSize;
            fontName = parent.fontName;
            width = parent.width;
            height = parent.height;
        }

        public static final Attributes DEFAULT = new Attributes();

        private Attributes parent;

        private Color color;
        private String label;
        private Shape shape;
        private double fontSize;
        private String fontName;
        private double width;
        private double height;

        public Attributes createChild() {
            return new Attributes(this);
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

        public void setColor(Color color) {
            this.color = color;
        }

        public String getLabel() {
            return label;
        }

        public void setLabel(String label) {
            this.label = label;
        }

        public Shape getShape() {
            return shape;
        }

        public void setShape(Shape shape) {
            this.shape = shape;
        }

        public double getFontSize() {
            return fontSize;
        }

        public void setFontSize(double fontSize) {
            this.fontSize = fontSize;
        }

        public String getFontName() {
            return fontName;
        }

        public void setFontName(String f) {
            fontName = f;
        }

        public double getWidth() {
            return width;
        }

        public void setWidth(double w) {
            width = w;
        }

        public double getHeight() {
            return height;
        }

        public void setHeight(double h) {
            height = h;
        }
    }

    public Node(Attributes attributes, String name) {
        this.attributes = attributes;
        this.name = name;
    }

    private Attributes attributes;
    private String name;

    public <T> void accept(GraphVisitor<T> visitor, T t) {
        visitor.visit(this, t);
    }

    public Attributes getAttributes() {
        return attributes;
    }

    public String getName() {
        return name;
    }
}

package edu.phuentelmann.danger.demo.diagram;

import java.io.FileOutputStream;
import java.io.PrintStream;

import edu.phuentelmann.danger.diagram.graphviz.DotGraphVisitor;
import edu.phuentelmann.danger.diagram.graphviz.Graph;
import edu.phuentelmann.danger.diagram.graphviz.GraphVizInvoker;
import edu.phuentelmann.danger.diagram.graphviz.UmlGraphBuilder;
import edu.phuentelmann.danger.diagram.graphviz.UmlGraphBuilder.ClassBuilder.Visibility;
import edu.phuentelmann.danger.diagram.graphviz.UmlGraphBuilder.RelationshipBuilder.Type;

public class DiagramDemo {
    public static void main(String[] args) {
        GraphVizInvoker gi = new GraphVizInvoker();
        try {
            gi.invoke(
                    (in) -> {
                        final Graph g = new UmlGraphBuilder()
                            .addClass("Foo", (x) -> {
                                x.addField(Visibility.Private, "foo", "String");
                                x.addMethod(Visibility.Public, "foobar", "String", (m) -> m.addParameter("bar", "int"));
                                x.addMethod(Visibility.Protected, "baz", "int", (m) -> {});
                            })
                            .addClass("Bar", (x) -> {
                                x.addMethod(Visibility.Public, "bar", "String", (m) -> {});
                            })
                            .addRelationship(Type.Inheritance, "Bar", "Foo")
                            .addRelationship(Type.Aggregation, "Bar", "Baz")
                            .addClass("Baz", (x) -> {})
                            .build();

                        g.accept(new DotGraphVisitor(), System.out);
                        g.accept(new DotGraphVisitor(), new PrintStream(in, true));
                    },
                    (out, err) -> {
                        if (err.available() > 0) {
                            System.err.write(err.readAllBytes());
                        }
                        if (out.available() > 0) {
                            try (FileOutputStream fs = new FileOutputStream("diag.svg")) {
                                fs.write(out.readAllBytes());
                                System.out.println("Diagram saved as diag.svg");
                            }
                        }
                        else {
                            System.out.println("Nothing done :(");
                        }
                    }
            );
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

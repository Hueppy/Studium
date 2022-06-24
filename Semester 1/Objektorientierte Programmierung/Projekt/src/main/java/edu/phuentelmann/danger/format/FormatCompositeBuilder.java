package edu.phuentelmann.danger.format;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Collectors;

/**
 * Builder class for format composites (e.g. Bold, Quote, ...)
 */
public class FormatCompositeBuilder extends FormatBuilder {
    public FormatCompositeBuilder(Function<List<FormatBase>, FormatBase> factory) {
        this.factory = factory;
        subBuilder = new ArrayList<>();
    }

    private final Function<List<FormatBase>, FormatBase> factory;
    private final List<FormatBuilder> subBuilder;

    protected void addItem(Supplier<FormatBase> factory) {
        this.subBuilder.add(new FormatBuilder() {
            @Override
            protected FormatBase buildItem() {
                return factory.get();
            }
        });
    }

    protected FormatCompositeBuilder addCollection(
            Function<List<FormatBase>, FormatBase> factory,
            Consumer<FormatCompositeBuilder> initializer) {
        FormatCompositeBuilder fcb = new FormatCompositeBuilder(factory);
        initializer.accept(fcb);
        this.subBuilder.add(fcb);
        return fcb;
    }

    public FormatCompositeBuilder addText(String s) {
        addItem(() -> new Text(s));
        return this;
    }

    public FormatCompositeBuilder addMonospacedText(String s) {
        addItem(() -> new MonospacedText(s));
        return this;
    }

    public FormatCompositeBuilder addHeader(int level, Consumer<FormatCompositeBuilder> initializer) {
        addCollection((x) -> new Header(x, level), initializer);
        return this;
    }

    public FormatCompositeBuilder addListItem(Consumer<FormatCompositeBuilder> initializer) {
        addCollection((x) -> new UnorderedListItem(x), initializer);
        return this;
    }

    public FormatCompositeBuilder addLink(String target, Consumer<FormatCompositeBuilder> initializer) {
        addCollection((x) -> new Link(x, target), initializer);
        return this;
    }

    public FormatCompositeBuilder addItalic(Consumer<FormatCompositeBuilder> initializer) {
        addCollection((x) -> new Italic(x), initializer);
        return this;
    }

    public FormatCompositeBuilder addBold(Consumer<FormatCompositeBuilder> initializer) {
        addCollection((x) -> new Bold(x), initializer);
        return this;
    }

    @Override
    protected FormatBase buildItem() {
        return factory.apply(
                subBuilder.stream()
                        .map((b) -> b.buildItem())
                        .collect(Collectors.toList()));
    }

    public FormatCompositeBuilder addSubCollection() {
        return addCollection(FormatCollection::new, (b) -> {});
    }

    public FormatComposite build() {
        return (FormatCollection)buildItem();
    }
}

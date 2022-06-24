package edu.phuentelmann.danger.format.markdown;
import edu.phuentelmann.danger.format.*;

import java.util.Stack;

public class MarkdownFormatVisitor implements FormatVisitor {
    private interface Strategy {
        void accept(String text);
        String getResult();
    }

    private class AppendingStrategy implements Strategy {
        public AppendingStrategy() {
            sb = new StringBuilder();
        }

        private final StringBuilder sb;

        @Override
        public void accept(String text) {
            sb.append(text);
        }

        @Override
        public String getResult() {
            return sb.toString();
        }
    }

    private class WrapStrategy extends AppendingStrategy {
        public WrapStrategy(String wrapper) {
            super();
            this.wrapper = wrapper;
        }

        private final String wrapper;

        @Override
        public String getResult() {
            final String inner = super.getResult().strip();

            if (inner.isBlank()) {
                return "";
            } else {
                return wrapper + super.getResult().strip() + wrapper;
            }
        }
    }

    private class PrefixedLineStrategy extends AppendingStrategy {
        public PrefixedLineStrategy(String prefix) {
            super();
            this.prefix = prefix;
        }

        private final String prefix;

        @Override
        public String getResult() {
            final String inner = super.getResult().strip();

            if (inner.isBlank()) {
                return "";
            } else {
                return "\n" + prefix + inner + "\n";
            }
        }
    }

    private class LinkStrategy extends AppendingStrategy {
        public LinkStrategy(String target) {
            super();
            this.target = target;
        }

        private final String target;

        @Override
        public String getResult() {
            return String.format("[%s](%s)", super.getResult().strip(), target);
        }
    }

    public MarkdownFormatVisitor() {
        baseStrategy = new AppendingStrategy();
        strategies = new Stack<>();
        strategies.push(baseStrategy);
    }

    private Stack<Strategy> strategies;
    private Strategy baseStrategy;

    private void accept(String text) {
        strategies.peek().accept(text);
    }

    private String formatMonospaced(String text) {
        return String.format("`%s`", text);
    }

    @Override
    public void beginVisit(Bold bold) {
        strategies.push(new WrapStrategy("**"));
    }

    @Override
    public void beginVisit(Header header) {
        strategies.push(new PrefixedLineStrategy("#".repeat(header.getLevel()) + " "));
    }

    @Override
    public void beginVisit(Italic italic) {
        strategies.push(new WrapStrategy("_"));
    }

    @Override
    public void beginVisit(Link link) {
        strategies.push(new LinkStrategy(link.getTarget()));
    }

    @Override
    public void beginVisit(Quote quote) {
        strategies.push(new PrefixedLineStrategy(">"));
    }

    @Override
    public void beginVisit(UnorderedListItem listItem) {
        strategies.push(new PrefixedLineStrategy(" * "));
    }

    @Override
    public void endVisit() {
        Strategy strategy = strategies.pop();
        accept(strategy.getResult());
    }

    @Override
    public void visit(MonospacedText text) {
        accept(formatMonospaced(text.getText()));
    }

    @Override
    public void visit(Text text) {
        accept(
            text.getText()
                .replace("<", "&lt;")
                .replace(">", "&gt;"));
    }

    public String getResult() {
        if (strategies.peek() != baseStrategy) {
            throw new UnsupportedOperationException("Current strategy was not base strategy - you cannot access result of visitor while visiting, otherwise this should never happen");
        }

        return baseStrategy.getResult();
    }
}

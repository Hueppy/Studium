package edu.phuentelmann.danger.utils;

import java.util.function.Supplier;

/**
 * Respresents a lazy indirection.
 * Normally this is a type created upon first usage.
 */
public final class Lazy<T> implements Supplier<T> {
    public Lazy(Supplier<T> factory) {
       this.factory = factory;
       this.value = null;
    }

    public Lazy(T value) {
        this.factory = null;
        this.value = value;
    }

    private final Supplier<T> factory;
    private T value;

    @Override
    public T get() {
        if (value == null) {
            value = factory.get();
        }
        return value;
    }

    public boolean isValueCreated() {
        return value != null;
    }
}

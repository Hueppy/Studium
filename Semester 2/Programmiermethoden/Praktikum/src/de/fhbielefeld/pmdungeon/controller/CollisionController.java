package de.fhbielefeld.pmdungeon.controller;

import de.fhbielefeld.pmdungeon.entities.Collidable;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Dictionary;
import java.util.List;
import java.util.function.BiConsumer;
import java.util.stream.Collectors;

/** Steuert die Kollision. */
public class CollisionController {
  private final List<SubController> subControllers;
  private final Dictionary<Class, SubController> lookup;
  private final List<List<? extends Collidable>> collidables;

  /** Erstellt einen Collision Controller. */
  public CollisionController() {
    this.subControllers = new ArrayList<>();
    this.lookup = new java.util.Hashtable<>();
    this.collidables = new ArrayList<>();
  }

  private SubController getControllerFor(Class selfClass) {
    if (selfClass == null) {
      return null;
    }

    SubController controller = lookup.get(selfClass);
    if (controller != null) {
      return controller;
    }

    controller =
        this.subControllers.stream()
            .filter((x) -> x.getSelfClass() == selfClass)
            .findFirst()
            .orElseGet(() -> getControllerFor(selfClass.getSuperclass()));
    if (controller != null) {
      lookup.put(selfClass, controller);
    }
    return controller;
  }

  /**
   * Registrieren einer kollidierbaren Entität am Controller.
   *
   * @param c kollidierbare Entität
   */
  public void registerCollidable(Collidable c) {
    collidables.add(List.of(c));
  }

  /**
   * Registrieren mehrer kollidierbarer Entitäten am Controller.
   *
   * @param c Liste von kollidierbaren Entitäten
   */
  public void registerCollidables(List<? extends Collidable> c) {
    collidables.add(c);
  }

  /**
   * Registriert einen neuen Handler am Controller.
   *
   * @param self Klasse der Entität
   * @param other Klasse der anderen Entität
   * @param handler Verhalten der Kollision
   * @param <T> Generictyp der Entität
   * @param <O> Generictyp der anderen Entität
   */
  public <T, O> void registerHandler(Class<T> self, Class<O> other, BiConsumer<T, O> handler) {
    SubController controller = getControllerFor(self);
    if (controller == null) {
      controller = new SubController(self);
      subControllers.add(controller);
    }
    controller.register(other, handler);
  }

  private List<Collidable> getCollidables() {
    return collidables.stream().flatMap(Collection::stream).collect(Collectors.toList());
  }

  /** Update-Methode des CollisionControllers. */
  public void update() {
    List<Collidable> collidables = getCollidables();

    Hashtable hashtable = new Hashtable(Math.max(collidables.size(), 10) * 2 - 1);

    for (Collidable c : collidables) {
      hashtable.add(c);
    }

    for (Tile t : hashtable.getKeys()) {
      List<Collidable> collisions = hashtable.getAll(t);

      for (Collidable self : collisions) {
        SubController controller = getControllerFor(self.getClass());
        if (controller == null) {
          continue;
        }

        for (Collidable other : collisions) {
          if (self != other) {
            controller.handle(self, other);
          }
        }
      }
    }
  }

  private static class Hashtable {
    private final Collidable[] buckets;
    private final List<Tile> keys;

    public Hashtable(int n) {
      buckets = new Collidable[n];
      keys = new ArrayList<>();
    }

    private int hash(Tile key) {
      return key.getX() + key.getY() * (int)Math.sqrt(buckets.length);
    }

    public void add(Collidable c) {
      Tile t = c.getTile();
      int hash = hash(t);
      int i = 0;
      int index = hash % buckets.length;
      boolean keyExists = false;
      while (buckets[index] != null) {
        Tile other = buckets[index].getTile();
        keyExists |= other.getX() == t.getX() && other.getY() == t.getY();
        i++;
        index = (hash + i * i) % buckets.length;
      }
      if (!keyExists) {
        keys.add(t);
      }
      buckets[index] = c;
    }

    public List<Collidable> getAll(Tile t) {
      List<Collidable> result = new ArrayList<>();
      int hash = hash(t);
      int i = 0;
      int index = hash % buckets.length;
      while (index >= 0 && buckets[index] != null) {
        Tile u = buckets[index].getTile();
        if (t.getX() == u.getX() && t.getY() == u.getY()) {
          result.add(buckets[index]);
        }

        i++;
        index = (hash + i * i) % buckets.length;
      }
      return result;
    }

    public List<Tile> getKeys() {
      return keys;
    }
  }

  private static class SubController {
    private final Class selfClass;
    private final List<Handler> handlers;
    private final Dictionary<Class, Handler> lookup;

    public SubController(Class selfClass) {
      this.selfClass = selfClass;
      this.handlers = new ArrayList<>();
      this.lookup = new java.util.Hashtable<>();
    }

    private Handler getHandlerFor(Class otherClass) {
      if (otherClass == null) {
        return null;
      }

      Handler handler = lookup.get(otherClass);
      if (handler != null) {
        return handler;
      }

      handler =
          this.handlers.stream()
              .filter((x) -> x.getHandledClass() == otherClass)
              .findFirst()
              .orElseGet(() -> getHandlerFor(otherClass.getSuperclass()));
      if (handler != null) {
        lookup.put(otherClass, handler);
      }
      return handler;
    }

    public Class getSelfClass() {
      return selfClass;
    }

    public void handle(Collidable self, Collidable other) {
      Handler h = getHandlerFor(other.getClass());
      if (h != null) {
        h.handle(self, other);
      }
    }

    public void register(Class other, BiConsumer handler) {
      handlers.add(new Handler(other, handler));
    }

    private static class Handler {
      private final Class handledClass;
      private final BiConsumer handler;

      public Handler(Class handledClass, BiConsumer handler) {
        this.handledClass = handledClass;
        this.handler = handler;
      }

      public Class getHandledClass() {
        return handledClass;
      }

      public void handle(Collidable self, Collidable other) {
        handler.accept(self, other);
      }
    }
  }
}

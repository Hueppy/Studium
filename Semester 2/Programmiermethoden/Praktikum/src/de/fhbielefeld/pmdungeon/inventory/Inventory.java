package de.fhbielefeld.pmdungeon.inventory;

import de.fhbielefeld.pmdungeon.entities.Item;
import de.fhbielefeld.pmdungeon.observers.InventoryObserver;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

/**
 * Implementierung eines Inventars
 *
 * <p>Das Inventar ist wie ein Rucksack implementiert, so lange Platz ist kann man darin Gegenstände
 * legen und beinhaltete Gegenstände entfernen.
 */
public class Inventory<T extends Item> {
  private static final Logger logger = Logger.getLogger(Inventory.class.getName());
  private final T[] items;
  private final List<InventoryObserver> observers;

  public Inventory(int capacity) {
    this.items = (T[]) new Item[capacity];
    this.observers = new ArrayList<>();
  }

  /**
   * Gegenstand in das Inventar legen.
   *
   * <p>Ist das Inventar voll schlägt das Hinzufügen
   *
   * @param item Gegenstand
   * @return Erfolgreiche Eingabe
   */
  public boolean add(T item) {
    boolean inserted = false;
    for (int i = 0; i < items.length; i++) {
      if (items[i] == null) {
        items[i] = item;
        inserted = true;
        break;
      }
    }

    if (inserted) {
      notify(InventoryAction.Add, item);
    }

    return inserted;
  }

  /**
   * Gegenstand aus dem Inventar entfernen.
   *
   * @param index Index des Elements
   * @return der Gegenstand an dem Index, falls dieser existiert
   */
  public Item remove(int index) {
    Item i = items[index];
    items[index] = null;
    if (i != null) {
      notify(InventoryAction.Remove, i);
    }
    return i;
  }

  /**
   * Gibt den Gegenstand aus dem Inventar zurück ohne diesen zu entfernen.
   *
   * @param index Index des Elements
   * @return Gegenstand an dem Index
   */
  public Item peek(int index) {
    return items[index];
  }

  /** Inventar darstellen. */
  public void show() {
    StringBuilder sb = new StringBuilder();
    sb.append("<Inventory>\n");
    for (int i = 0; i < items.length; i++) {
      if (items[i] != null) {
        sb.append(String.format("<%d> %s\n", i, items[i]));
      }
    }
    logger.info(sb.toString());
  }

  private void notify(InventoryAction action, Item item) {
    // copy observers for iteration
    List<InventoryObserver> observers = new ArrayList<>(this.observers);
    for (InventoryObserver observer : observers) {
      observer.update(action, item);
    }
  }

  /** Registriert einen InventoryObserver am Inventar. */
  public void register(InventoryObserver observer) {
    this.observers.add(observer);
  }

  /** Unregistriert einen InventoryObserver vom Inventar. */
  public void unregister(InventoryObserver observer) {
    this.observers.remove(observer);
  }

  public int getCapacity() {
    return items.length;
  }
}

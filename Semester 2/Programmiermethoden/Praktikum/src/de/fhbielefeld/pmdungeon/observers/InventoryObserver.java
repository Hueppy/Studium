package de.fhbielefeld.pmdungeon.observers;

import de.fhbielefeld.pmdungeon.entities.Item;
import de.fhbielefeld.pmdungeon.inventory.InventoryAction;

/** Observer für ein Inventar. */
public interface InventoryObserver {
  /**
   * Methode, die Aufgerufen wird, wenn das Observierte Inventar sich ändert.
   *
   * @param action Aktion (Add oder Remove)
   * @param item Item
   */
  void update(InventoryAction action, Item item);
}

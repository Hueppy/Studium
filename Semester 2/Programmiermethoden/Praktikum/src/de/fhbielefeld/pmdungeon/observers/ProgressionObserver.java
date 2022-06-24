package de.fhbielefeld.pmdungeon.observers;

import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;

/** Observer für den Wechsel in das nöchste Level. */
public interface ProgressionObserver {
  /**
   * Methode die beim Levelfortschritt aufgerufen wird.
   *
   * @param level Neues Level
   */
  void update(DungeonWorld level);
}

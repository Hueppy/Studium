package de.fhbielefeld.pmdungeon.entities;

import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;

/** Liefert Kollisionsinformationen von kollidierbaren Entitäten. */
public interface Collidable {
  /**
   * Aktuelles Tile der Entität.
   *
   * @return Tile
   */
  Tile getTile();
}

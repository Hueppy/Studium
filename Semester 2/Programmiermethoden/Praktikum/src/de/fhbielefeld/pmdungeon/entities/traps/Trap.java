package de.fhbielefeld.pmdungeon.entities.traps;

import de.fhbielefeld.pmdungeon.entities.Character;
import de.fhbielefeld.pmdungeon.entities.Collidable;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.dungeonconverter.Coordinate;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IDrawable;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Basisklasse für eine Falle. */
public abstract class Trap implements IEntity, IDrawable, Collidable {
  private Point position;
  private DungeonWorld dungeon;

  /**
   * In dieser Methode wird das Verhalten der Falle implementiert.
   *
   * @param character Charakter, der die Falle aktiviert hat
   */
  public abstract void activate(Character character);

  @Override
  public void draw(float xoffset, float yoffset, float xscaling, float yscaling) {
    IDrawable.super.draw(0f, 0f, xscaling, yscaling);
  }

  @Override
  public Point getPosition() {
    return position;
  }

  @Override
  public void update() {
    this.draw();
  }

  @Override
  public boolean deleteable() {
    return false;
  }

  public DungeonWorld getDungeon() {
    return dungeon;
  }

  /** Setzt den Dungeon der Falle. */
  public void setDungeon(DungeonWorld dungeon) {
    this.dungeon = dungeon;
    Coordinate coordinate = dungeon.getRandomLocationInDungeon();
    this.position = new Point(coordinate.getX(), coordinate.getY());
  }

  @Override
  public Tile getTile() {
    return dungeon.getTileAt((int) position.x, (int) position.y);
  }
}

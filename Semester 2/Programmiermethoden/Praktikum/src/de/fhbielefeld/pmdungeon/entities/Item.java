package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IDrawable;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Basisklasse für einen Gegenstand. */
public abstract class Item implements IEntity, IDrawable, Collidable {
  protected boolean consumed = false;
  private Point position;
  private Texture texture;
  private boolean visible = true;
  private boolean pickedup = false;
  private DungeonWorld level;

  /**
   * Factory Methode für die Textur des Gegenstands.
   *
   * @return die erstellte Textur
   */
  protected abstract Texture createTexture();

  /**
   * Benutzung des Gegenstands.
   *
   * @param character der Held der den Gegenstand benutzt
   */
  public abstract void use(Character character);

  public boolean isVisible() {
    return visible;
  }

  public void setVisible(boolean visible) {
    this.visible = visible;
  }

  @Override
  public Point getPosition() {
    return position;
  }

  public void setPosition(Point position) {
    this.position = position;
  }

  @Override
  public Texture getTexture() {
    if (texture == null) {
      texture = createTexture();
    }
    return texture;
  }

  @Override
  public void update() {
    if (visible) {
      this.draw();
    }
  }

  @Override
  public void draw() {
    draw(0f, 0f);
  }

  @Override
  public boolean deleteable() {
    return consumed;
  }

  public DungeonWorld getLevel() {
    return level;
  }

  public void setLevel(DungeonWorld level) {
    this.position = level.getRandomPointInDungeon();
    this.level = level;
  }

  public boolean isPickedUp() {
    return pickedup;
  }

  public void setPickedUp(boolean pickedup) {
    this.pickedup = pickedup;
  }

  public boolean isConsumed() {
    return consumed;
  }

  @Override
  public Tile getTile() {
    return level.getTileAt((int) position.x, (int) position.y);
  }
}

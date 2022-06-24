package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.inventory.Inventory;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IDrawable;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.ArrayList;
import java.util.List;

/** Implementierung einer Schatzkiste, welche Gegenstände beinhlaten kann. */
public class Chest implements IEntity, IDrawable, Collidable {
  private final Inventory<Item> inventory;
  private final Texture full;
  private final Texture empty;
  private Point position;
  private State state = State.Full;
  private DungeonWorld level;

  /** Erstelt eine neue Kiste mit dem übergebenen Inventar. */
  public Chest(Inventory<Item> inventory) {
    this.inventory = inventory;
    this.full = new Texture("assets/frames/chest_full_open_anim_f2.png");
    this.empty = new Texture("assets/frames/chest_empty_open_anim_f2.png");
  }

  @Override
  public Point getPosition() {
    return position;
  }

  @Override
  public Texture getTexture() {
    switch (state) {
      case Full:
        return full;
      case Empty:
        return empty;
      default:
        return null;
    }
  }

  @Override
  public void update() {
    this.draw();
  }

  @Override
  public void draw() {
    draw(0f, 0f);
  }

  @Override
  public boolean deleteable() {
    return false;
  }

  public DungeonWorld getLevel() {
    return level;
  }

  /** Setzt das aktuelle Level der Kiste. */
  public void setLevel(DungeonWorld level) {
    this.level = level;
    this.position = level.getRandomPointInDungeon();
    this.state = State.Full;
  }

  public Inventory<Item> getInventory() {
    return inventory;
  }

  /**
   * Leert das Inventar und gibt die Gegenstände zurück.
   *
   * @return die zuvor enthaltenen Gegenstände
   */
  public List<Item> empty() {
    List<Item> items = new ArrayList<>();
    for (int i = 0; i < inventory.getCapacity(); i++) {
      Item item = inventory.remove(i);
      if (item != null) {
        items.add(item);
      }
    }
    state = State.Empty;
    return items;
  }

  @Override
  public Tile getTile() {
    return level.getTileAt((int) position.x, (int) position.y);
  }

  private enum State {
    Full,
    Empty
  }
}

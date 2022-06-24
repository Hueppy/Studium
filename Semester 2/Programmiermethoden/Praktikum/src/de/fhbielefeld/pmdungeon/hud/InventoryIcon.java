package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.entities.Item;
import de.fhbielefeld.pmdungeon.inventory.Inventory;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IHUDElement;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/**
 * Inventardarstellung.
 *
 * @param <T> Generictyp des Inventars
 */
public class InventoryIcon<T extends Item> implements IHUDElement {
  private static final Texture empty = new Texture(1, 1, Pixmap.Format.Alpha);
  private final Point position;
  private final Inventory<T> inventory;
  private final int slot;

  /** Erstellt ein neues Icon für die Inventaranzeige. */
  public InventoryIcon(Inventory<T> inventory, int slot) {
    this.inventory = inventory;
    this.slot = slot;

    this.position = new Point(0.5f * (1 + slot), 0f);
  }

  @Override
  public Point getPosition() {
    Point position = new Point(this.position);
    position.x += 1 - (getWidth() / 2);
    return position;
  }

  @Override
  public Texture getTexture() {
    Item item = inventory.peek(slot);
    if (item == null) {
      return empty;
    }

    return item.getTexture();
  }

  @Override
  public float getHeight() {
    Texture texture = getTexture();
    return texture.getWidth() / 2;
  }

  @Override
  public float getWidth() {
    final Texture texture = getTexture();
    return (float) texture.getWidth() / (float) texture.getHeight() / 2;
  }
}

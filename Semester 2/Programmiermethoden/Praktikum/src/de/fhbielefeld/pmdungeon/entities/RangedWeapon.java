package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IDrawable;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.function.Consumer;

/** Fernkampfwaffe. */
public class RangedWeapon extends Weapon {
  private final Consumer<IEntity> addEntity;
  private Character owner;

  public RangedWeapon(Consumer<IEntity> addEntity) {
    this.addEntity = addEntity;
  }

  @Override
  public void attack(Point direction) {
    DungeonWorld level = getLevel();
    if (level == null) {
      return;
    }

    Point position = new Point(getPosition());
    position.x += 1f;

    addEntity.accept(
        new Projectile(
            position, direction, level, new Texture("assets/frames/weapon_knife.png"), this));
  }

  @Override
  public void use(Character character) {
    this.owner = character;
    super.use(character);
  }

  @Override
  public int getAttack() {
    return 50;
  }

  @Override
  public String getWeaponName() {
    return "AWP Akimbo";
  }

  @Override
  protected Texture createTexture() {
    return new Texture("assets/frames/weapon_green_magic_staff.png");
  }

  public Character getOwner() {
    return owner;
  }

  /** Projektil der Fernkampfwaffe. */
  public class Projectile implements IEntity, IDrawable, Collidable {
    private final DungeonWorld level;
    private final Point position;
    private final Point direction;
    private final Texture texture;
    private final RangedWeapon owner;

    /** Erstellt ein neues Projektil. */
    public Projectile(
        Point startPoint,
        Point direction,
        DungeonWorld level,
        Texture texture,
        RangedWeapon owner) {
      this.position = startPoint;
      this.direction = direction;
      this.level = level;
      this.texture = texture;
      this.owner = owner;
    }

    @Override
    public void draw(float xoffset, float yoffset, float xscaling, float yscaling) {
      IDrawable.super.draw(xoffset, yoffset, 0.3f, 0.3f);
    }

    @Override
    public Point getPosition() {
      return position;
    }

    @Override
    public Texture getTexture() {
      return texture;
    }

    @Override
    public void update() {
      draw();
      position.x += direction.x;
      position.y += direction.y;
    }

    @Override
    public boolean deleteable() {
      return !level.isTileAccessible(position);
    }

    @Override
    public Tile getTile() {
      return level.getTileAt((int) position.x, (int) position.y);
    }

    public RangedWeapon getOwner() {
      return owner;
    }
  }
}

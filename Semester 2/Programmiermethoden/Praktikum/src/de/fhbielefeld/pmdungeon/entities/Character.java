package de.fhbielefeld.pmdungeon.entities;

import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import de.fhbielefeld.pmdungeon.vorgaben.graphic.Animation;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IAnimatable;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.Random;
import java.util.logging.Logger;

/** Basisklasse für einen Charakter. */
public abstract class Character implements IAnimatable, IEntity, Collidable {
  protected static final Point zero = new Point(0.0f, 0.0f);
  private static final Logger logger = Logger.getLogger(Character.class.getName());
  private static final Random random = new Random();
  private final int defaultHealth;
  private final int defaultAttack;
  protected Point position;
  protected Point velocity;
  protected int health;
  protected int attack;
  protected Weapon weapon;
  private DungeonWorld dungeon;

  /** Erstellt einen neuen Character mit den übergebenen Lebens- und Angriffspunkten. */
  public Character(int health, int attack) {
    this.defaultHealth = health;
    this.health = health;
    this.defaultAttack = attack;
    this.attack = attack;
  }

  protected void updateAttack() {
    int attack = defaultAttack;
    if (this.weapon != null) {
      attack = this.weapon.getAttack();
    }
    setAttack(attack);
  }

  /**
   * Getter der Idle-Animation.
   *
   * @return die Idle-Animation
   */
  protected abstract Animation getIdleAnimation();

  /**
   * Getter der Laufanimation.
   *
   * @return die Lauf-Animation
   */
  protected abstract Animation getWalkAnimation();

  /**
   * Abstrakte Methode zur Berechnung der Bewegung beim Update.
   *
   * @return Zweidimensionaler Richtungsvektor
   */
  protected abstract Point calculateVelocity();

  /**
   * Gibt die aktuelle Animation zurück.
   *
   * <p>Besteht eine Bewegung zur Seite wird die Laufanimation zurückgegeben, ansonsten die
   * Idle-Animation
   */
  @Override
  public Animation getActiveAnimation() {
    if (Math.abs(this.velocity.x) > 0) {
      return getWalkAnimation();
    }
    return getIdleAnimation();
  }

  /**
   * Getter für die aktuelle Position des Characters.
   *
   * @return Aktuelle Position
   */
  @Override
  public Point getPosition() {
    return this.position;
  }

  public void setPosition(Point position) {
    this.position = position;
  }

  /**
   * Überschreibung von IAnimatable.draw() um das Sprite zu Spiegeln, wenn der Character nach links
   * läuft
   */
  @Override
  public void draw(float xoffset, float yoffset, float xscaling, float yscaling) {
    // If velocity.x is negative make Scale negative as well
    final float xScale = Math.copySign(xscaling, velocity.x);
    // When we scale the Image in negative direction the origin of the picture
    // is shifted as well, so we do not need the offset anymore
    final float xOff = xScale > 0 ? xoffset : 0;

    IAnimatable.super.draw(xOff, yoffset, xScale, yscaling);
  }

  /**
   * Aktualisiert die Eigenschaften des Charakters.
   *
   * <p>Ruft calculateVelocity() auf um die aktuelle Bewegung zu bestimmen, wenn das nächste Tile
   * zugängig ist wird die Position entsprechend angepasst
   */
  @Override
  public void update() {
    this.velocity = calculateVelocity();

    Point newPosition =
        new Point(this.position.x + this.velocity.x, this.position.y + this.velocity.y);
    if (!this.dungeon.isTileAccessible(newPosition)) {
      this.velocity = zero;
      newPosition = position;
    }

    logger.fine(String.format("New velocity: (%f|%f)", this.velocity.x, this.velocity.y));

    this.draw();

    if (this.weapon != null) {
      Point position = new Point(this.position);
      boolean mirror = velocity.x < 0;
      position.x -= mirror ? 1.3f : 0.5f;
      position.y -= 0.1f;
      this.weapon.setPosition(position);
      this.weapon.setMirrored(mirror);
      this.weapon.update();
    }

    this.position = newPosition;
  }

  @Override
  public boolean deleteable() {
    return false;
  }

  public DungeonWorld getDungeon() {
    return dungeon;
  }

  /** Setzt das Level des Charakters. */
  public void setDungeon(DungeonWorld dungeon) {
    this.dungeon = dungeon;
    this.position = dungeon.getRandomPointInDungeon();
    if (this.weapon != null) {
      this.weapon.setLevel(dungeon);
    }
    logger.fine(String.format("New position: (%f, %f)", position.x, position.y));
  }

  /**
   * Verhalten bei einem erfolgreichem Angriff.
   *
   * @param other anzugreifender Character
   */
  protected void successfulAttack(Character other) {
    other.damage(this, this.attack);
  }

  /**
   * Greift den übergebenen Character an.
   *
   * @param other Anzugreifender Charakter
   */
  public void attack(Character other) {
    if (random.nextFloat() > 0.6) {
      successfulAttack(other);
    }
  }

  /**
   * Ausrüsten einer Waffe.
   *
   * @param weapon die auszurüstende Waffe
   */
  public void equip(Weapon weapon) {
    logger.info(String.format("Equipping %s", weapon));
    this.weapon = weapon;
    if (this.weapon != null) {
      this.weapon.setVisible(true);
    }
    updateAttack();
  }

  /**
   * Stellt Lebenspunkte wieder her.
   *
   * @param health die zuwiederherstellenden Lebenspunkte
   */
  public void restore(int health) {
    logger.info(String.format("restoring %d hp", health));
    this.health = Math.min(this.health + health, defaultHealth);
    logger.info(String.format("new health: %d hp", this.health));
  }

  /**
   * Zieht den übergebenen Schaden von den Lebenspunkten ab.
   *
   * @param from Herkunft des Schadens
   * @param damage Schadenspunkte
   */
  public void damage(Character from, int damage) {
    this.health -= damage;
  }

  public int getHealth() {
    return health;
  }

  public void setHealth(int health) {
    this.health = health;
  }

  public int getAttack() {
    return attack;
  }

  public void setAttack(int attack) {
    this.attack = attack;
  }

  @Override
  public Tile getTile() {
    return dungeon.getTileAt((int) position.x, (int) position.y);
  }

  public Weapon getWeapon() {
    return weapon;
  }
}

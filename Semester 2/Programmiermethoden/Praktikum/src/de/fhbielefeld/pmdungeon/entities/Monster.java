package de.fhbielefeld.pmdungeon.entities;

import de.fhbielefeld.pmdungeon.behaviors.BehaviorStrategy;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.logging.Logger;

/** Basisklasse für ein Monster. */
public abstract class Monster extends Character {
  private static final Logger logger = Logger.getLogger(Monster.class.getName());
  private BehaviorStrategy behavior;

  public Monster(int health, int attack) {
    super(health, attack);
  }

  @Override
  public void update() {
    if (behavior != null) {
      behavior.update();
    }
    super.update();
  }

  @Override
  public boolean deleteable() {
    boolean died = health <= 0;
    if (died && this.weapon != null) {
      this.weapon.consumed = true;
    }
    return died;
  }

  protected Point calculateVelocity() {
    if (velocity == null) {
      return zero;
    }

    return velocity;
  }

  public Point getVelocity() {
    return velocity;
  }

  public void setVelocity(Point velocity) {
    this.velocity = velocity;
  }

  public BehaviorStrategy getBehavior() {
    return behavior;
  }

  public void setBehavior(BehaviorStrategy behavior) {
    this.behavior = behavior;
  }
}

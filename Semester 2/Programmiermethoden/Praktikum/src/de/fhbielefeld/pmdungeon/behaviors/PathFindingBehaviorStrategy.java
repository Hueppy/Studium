package de.fhbielefeld.pmdungeon.behaviors;

import com.badlogic.gdx.ai.pfa.GraphPath;
import de.fhbielefeld.pmdungeon.entities.Monster;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.dungeonconverter.Coordinate;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;
import java.util.ArrayDeque;
import java.util.Queue;

/** Abstrakte Basisklasse für eine Verhaltensstrategie mit Path-Finding. */
public abstract class PathFindingBehaviorStrategy extends BehaviorStrategy {
  private static final Point zero = new Point(0.0f, 0.0f);
  protected final Queue<Tile> path;

  public PathFindingBehaviorStrategy(Monster monster) {
    super(monster);
    this.path = new ArrayDeque<>();
  }

  protected abstract Coordinate getTargetLocation();

  protected Point calculateVelocity() {
    DungeonWorld level = monster.getDungeon();
    Point position = monster.getPosition();

    while (this.path.isEmpty() || !this.path.peek().isAccessible()) {
      Coordinate current = new Coordinate((int) position.x, (int) position.y);
      Coordinate target = getTargetLocation();
      if (current.getX() == target.getX() && current.getY() == target.getY()) {
        return zero;
      }

      GraphPath<Tile> path = level.findPath(level.getTileAt(current), level.getTileAt(target));
      if (path.getCount() == 0) {
        return zero;
      }
      this.path.clear();
      for (Tile t : path) {
        this.path.add(t);
      }
      if (!this.path.isEmpty()) {
        this.path.remove();
      }
    }

    Point velocity = new Point(0f, 0f);
    Tile nextTarget = path.peek();

    final float movementSpeed = 0.1f;
    Point difference = new Point(nextTarget.getX() - position.x, nextTarget.getY() - position.y);
    if (Math.abs(difference.x) > movementSpeed) {
      velocity.x = Math.copySign(movementSpeed, difference.x);
    }

    if (Math.abs(difference.y) > movementSpeed) {
      velocity.y = Math.copySign(movementSpeed, difference.y);
    }

    if (Math.abs(difference.x) < movementSpeed && Math.abs(difference.y) < movementSpeed) {
      this.path.remove();
    }

    if (!level.isTileAccessible((int) (position.x + velocity.x), (int) (position.y + velocity.y))) {
      this.path.clear();
      return zero;
    }

    return velocity;
  }

  @Override
  public void update() {
    monster.setVelocity(calculateVelocity());
  }
}

package de.fhbielefeld.pmdungeon.entities;

import com.badlogic.gdx.graphics.Texture;
import de.fhbielefeld.pmdungeon.quests.Quest;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.dungeonconverter.Coordinate;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.tiles.Tile;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IDrawable;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;
import de.fhbielefeld.pmdungeon.vorgaben.tools.Point;

/** Questgeber. */
public class QuestGiver implements IEntity, IDrawable, Collidable {
  private final Point position;
  private final Texture texture = new Texture("assets/textures/dungeon/floor/floor_quest.png");
  private final DungeonWorld level;
  private final Quest quest;

  /** Erstellt einen neuen Questgeber. */
  public QuestGiver(DungeonWorld level, Quest quest) {
    Coordinate c = level.getRandomLocationInDungeon();
    this.level = level;
    this.position = new Point(c.getX(), c.getY());
    this.quest = quest;
  }

  @Override
  public void draw(float xoffset, float yoffset, float xscaling, float yscaling) {
    IDrawable.super.draw(0, 0, xscaling, yscaling);
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
    this.draw();
  }

  @Override
  public boolean deleteable() {
    return this.quest.isAssigned();
  }

  public Quest getQuest() {
    return quest;
  }

  @Override
  public Tile getTile() {
    return level.getTileAt((int) position.x, (int) position.y);
  }
}

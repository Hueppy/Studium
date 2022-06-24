package de.fhbielefeld.pmdungeon.quests;

import de.fhbielefeld.pmdungeon.entities.Item;
import de.fhbielefeld.pmdungeon.observers.ProgressionObserver;
import de.fhbielefeld.pmdungeon.vorgaben.dungeonCreator.DungeonWorld;
import java.util.List;
import java.util.logging.Logger;

/** Quest die bei Fortschritt im Dungeon erfüllt wird. */
public class ProgressionQuest extends Quest implements ProgressionObserver {
  private static final Logger logger = Logger.getLogger(ProgressionQuest.class.getName());

  /** Erstellt eine neue Fortschrittsquest. */
  public ProgressionQuest(int xp, List<Item> items) {
    super(xp, items);
  }

  @Override
  public void update(DungeonWorld level) {
    logger.info("Level progressed");
    finish();
  }

  @Override
  public String getDescription() {
    return "Progress the next level";
  }
}

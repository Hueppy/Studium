package de.fhbielefeld.pmdungeon.quests;

import de.fhbielefeld.pmdungeon.entities.Item;
import de.fhbielefeld.pmdungeon.inventory.InventoryAction;
import de.fhbielefeld.pmdungeon.observers.InventoryObserver;
import java.util.List;
import java.util.logging.Logger;

/** Quest bei der mehrere Items eines Typens gesammelt werden müssen. */
public class CollectingQuest extends Quest implements InventoryObserver {
  private static final Logger logger = Logger.getLogger(CollectingQuest.class.getName());
  private final Class<? extends Item> type;
  private int count;

  /** Erstellt eine neue Sammelquest. */
  public CollectingQuest(int xp, List<Item> items, Class<? extends Item> itemType, int itemCount) {
    super(xp, items);
    this.type = itemType;
    this.count = itemCount;
  }

  @Override
  public void update(InventoryAction action, Item item) {
    logger.info(String.format("Observed inventory changed <%s> [%s]", action, item));
    if (item.getClass() == this.type) {
      switch (action) {
        case Add:
          count--;
          break;
        case Remove:
          count++;
          break;
        default:
          break;
      }

      logger.info(String.format("New count: %d", count));

      if (count <= 0) {
        finish();
      }
    }
  }

  @Override
  public String getDescription() {
    return String.format("Collect %dx %s", count, type.getSimpleName());
  }
}

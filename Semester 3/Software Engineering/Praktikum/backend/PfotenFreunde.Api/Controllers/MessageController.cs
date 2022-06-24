using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class MessageController : ControllerBase
{
    private PfotenFreundeContext context;

    public MessageController(PfotenFreundeContext context)
    {
        this.context = context;
    }

    /// <summary>
    /// Deletes the message
    /// </summary>e
    /// <response code="404">Message not found</response>
    /// <response code="403">Insufficient permissions</response>
    [HttpDelete("{id}")]
    public ActionResult DeleteMessage(int id)
    {
        return this.WithCurrentUser(context, user =>
        {
            var message = context.Messages.Find(id);
            if (message == null)
            {
                return NotFound();
            }
            
            if (!this.IsAdministrator() || user.Id != message.SenderId)
            {
                return Forbid();
            }

            context.Messages.Remove(message);
            context.SaveChanges();
            
            return Ok();
        });
    }
}

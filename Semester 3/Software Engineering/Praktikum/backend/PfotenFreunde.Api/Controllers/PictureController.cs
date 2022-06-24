using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class PictureController : ControllerBase
{
    private PfotenFreundeContext context;

    public PictureController(PfotenFreundeContext context)
    {
        this.context = context;
    }

    /// <summary>
    /// Deletes the picture
    /// </summary>e
    /// <response code="404">Picture not found</response>
    /// <response code="403">Insufficient permissions</response>
    [HttpDelete("{id}")]
    public ActionResult DeletePicture(int id)
    {
        return this.WithCurrentUser(context, user =>
        {
            var picture = context.Pictures.Find(id);
            if (picture == null)
            {
                return NotFound();
            }
            
            if (!this.IsAdministrator() || user.Id != picture.UploaderId)
            {
                return Forbid();
            }

            context.Pictures.Remove(picture);
            context.SaveChanges();
            
            return Ok();
        });
    }
}

using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class PostController : ControllerBase
{
    private PfotenFreundeContext context;

    public PostController(PfotenFreundeContext context)
    {
        this.context = context;
    }

    /// <summary>
    /// Deletes the post
    /// </summary>e
    /// <response code="404">Post not found</response>
    /// <response code="403">Insufficient permissions</response>
    [HttpDelete("{id}")]
    public ActionResult DeletePost(int id)
    {
        return this.WithCurrentUser(context, user =>
        {
            var post = context.Posts.Find(id);
            if (post == null)
            {
                return NotFound();
            }
            
            if (!this.IsAdministrator() || user.Id != post.UserId)
            {
                return Forbid();
            }

            context.Posts.Remove(post);
            context.SaveChanges();
            
            return Ok();
        });
    }

    [HttpGet("{id}/pictures")]
    public IEnumerable<Picture> GetPictures(int id)
    {
        var ids = context.PicturePosts
            .Where(x => x.PostId == id)
            .Select(x => x.Id);
        
        return context.Pictures.Where(x => ids.Contains(x.Id));
    }

    [HttpPost("{id}/picture")]
    public async Task PostPicture(int id, IFormFile file)
    {
        using var stream = new MemoryStream();
        await file.CopyToAsync(stream);

        var picture = new PicturePost()
        {
            PostId = id,
            Picture = new Picture()
            {
                UploadDate = DateTime.Now,
                Data = stream.ToArray()    
            }
        };
        await context.PicturePosts.AddAsync(picture);
        await context.SaveChangesAsync();
    }
}

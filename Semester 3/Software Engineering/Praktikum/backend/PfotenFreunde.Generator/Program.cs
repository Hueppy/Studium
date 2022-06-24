using GenFu;
using Microsoft.EntityFrameworkCore;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;
using PfotenFreunde.Shared.Services;

using Attribute = PfotenFreunde.Shared.Models.Attribute;

var context = new PfotenFreundeContext();
var hasher = new PasswordHasher();
	
void Generate<T>(DbSet<T> set, int count = 25)
	where T : class, new()
{
	set.AddRange(A.ListOf<T>(count));
}

void GenerateDistinct<T, TKey>(DbSet<T> set, Func<T, TKey> keySelector, int limit = 25)
	where T : class, new()
{
	set.AddRange(A.ListOf<T>(limit).DistinctBy(keySelector));	
}

HashSet<T> SelectRandom<T>(IEnumerable<T> collection, int limit = 10)
{
	var collectionCount = collection.Count();
	var random = GenFu.GenFu.Random;
	var count = Math.Min(random.Next(limit), collectionCount);
	var list = new HashSet<T>();
	for (int i = 0; i < count; i++) {
		list.Add(collection.ElementAt(random.Next(collectionCount)));
	}
	return list;
}

GenFu.GenFu.Configure<Address>()
	.Fill(x => x.Id, 0)
	.Fill(x => x.Zip, () => GenFu.GenFu.Random.NextInt64(0, 9999999999).ToString());
GenFu.GenFu.Configure<Chronicle>()
	.Fill(x => x.Id, 0);

Generate(context.Addresses, 200);
Generate(context.Chronicles, 200);

context.SaveChanges();

var addressIds = context.Addresses.Select(x => x.Id);

GenFu.GenFu.Configure<User>()
	.Fill(x => x.Id, 0)
	.Fill(x => x.AddressId).WithRandom(addressIds)
	.Fill<Login>(x => x.Login, (x) =>
          new Login()
          {
              Email = x.Email,
              PasswordHash = hasher.HashPassword(null, "correct horse battery staple")
          });
GenFu.GenFu.Configure<Person>()
	.Fill(x => x.InstitutionId, () => null);

Generate(context.Institutions, 25);
Generate(context.People, 50);

context.SaveChanges();

var institutionIds = context.Institutions.Select(x => (int?)x.Id);

GenFu.GenFu.Configure<Person>()
	.Fill(x => x.InstitutionId).WithRandom(institutionIds);

Generate(context.People, 100);

context.SaveChanges();

var userIds = context.Users.Select(x => x.Id).AsEnumerable();
var userCount = userIds.Count();

for (int i = 0; i < 20; ++i) {
    foreach (var file in Directory.GetFiles("pictures"))
    {
        var ext = Path.GetExtension(file);
        if (ext == ".jpg" || ext == ".png")
        {
            var picture = new Picture()
            {
                Id = 0,
                UploadDate = DateTime.Now,
                UploaderId = userIds.ElementAt(GenFu.GenFu.Random.Next(userCount)),
                Data = File.ReadAllBytes(file)
            };
            context.Pictures.Add(picture);
        }
    }
    context.SaveChanges();
}

var chronicleIds = context.Chronicles.Select(x => x.Id);
var pictureIds = context.Pictures.Select(x => x.Id);
var personIds = context.People.Select(x => x.Id);

GenFu.GenFu.Configure<FriendRequest>()
    .Fill(x => x.Id, 0)
    .Fill(x => x.SenderId).WithRandom(userIds)
	.Fill(x => x.SenderId).WithRandom(userIds)
	.Fill(x => x.ReceiverId).WithRandom(userIds);
GenFu.GenFu.Configure<Rating>()
    .Fill(x => x.Id, 0)
    .Fill(x => x.UserId).WithRandom(userIds)
    .Fill(x => x.SenderId).WithRandom(userIds);
GenFu.GenFu.Configure<Post>()
    .Fill(x => x.Id, 0)
    .Fill(x => x.UserId).WithRandom(userIds)
    .Fill(x => x.ChronicleId).WithRandom(chronicleIds)
	.Fill(x => x.Message).AsLoremIpsumSentences();
GenFu.GenFu.Configure<Chatroom>()
	.Fill(x => x.Id, 0)
	.Fill(x => x.Users, () => SelectRandom(context.Users));
GenFu.GenFu.Configure<Report>()
	.Fill(x => x.Id, 0)
	.Fill(x => x.UserId).WithRandom(userIds)
	.Fill(x => x.SenderId).WithRandom(userIds);
GenFu.GenFu.Configure<Pet>()
	.Fill(x => x.Id, 0)
	.Fill(x => x.OwnerId).WithRandom(personIds);

Generate(context.FriendRequests, 100);
Generate(context.Ratings, 2000);
Generate(context.Posts, 500);
Generate(context.Chatrooms, 50);
Generate(context.Reports, 50);
Generate(context.Pets, 250);

context.SaveChanges();

var chatroomIds = context.Chatrooms.Select(x => x.Id);
var petIds = context.Pets.Select(x => x.Id);
var postIds = context.Posts.Select(x => x.Id);

GenFu.GenFu.Configure<Message>()
    .Fill(x => x.Id, 0)
    .Fill(x => x.SenderId).WithRandom(userIds)
	.Fill(x => x.ChatroomId).WithRandom(chatroomIds)
	.Fill(x => x.Text).AsLoremIpsumSentences();
GenFu.GenFu.Configure<Attribute>()
	.Fill(x => x.Id, 0)
	.Fill(x => x.PetId).WithRandom(petIds);
GenFu.GenFu.Configure<Preference>()
	.Fill(x => x.Id, 0)
	.Fill(x => x.PetId).WithRandom(petIds);
GenFu.GenFu.Configure<PicturePet>()
	.Fill(x => x.Id).WithRandom(pictureIds)
	.Fill(x => x.PetId).WithRandom(petIds);
GenFu.GenFu.Configure<PicturePost>()
	.Fill(x => x.Id).WithRandom(pictureIds)
	.Fill(x => x.PostId).WithRandom(postIds);
GenFu.GenFu.Configure<PictureUser>()
	.Fill(x => x.Id).WithRandom(pictureIds)
	.Fill(x => x.UserId).WithRandom(userIds);

Generate(context.Messages, 500);
Generate(context.Attributes, 1000);
Generate(context.Preferences, 1000);
GenerateDistinct(context.PicturePets, x => x.Id, 50);
GenerateDistinct(context.PicturePosts, x => x.Id, 100);
GenerateDistinct(context.PictureUsers, x => x.Id, 50);

context.SaveChanges();


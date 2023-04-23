class Student < ApplicationRecord
  validates :matrikel, presence: true, format: /\d+/, length: { minimum: 1 }
  validates :first_name, presence: true, length: { minimum: 1 }
  validates :last_name, presence: true, length: { minimum: 1 }
end

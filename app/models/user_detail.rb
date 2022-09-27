class UserDetail < ApplicationRecord
    belongs_to :floor


    validates :client_name ,:car_color, presence: true,  
    length: {maximum: 30}

    validates :email, presence: true, uniqueness: { case_sensitive: false }, length: {maximum: 50}
    
    
  
    
    validates :in_time, :out_time ,presence: true

    validates :car_number,  presence: true, 
    uniqueness: { case_sensitive: false }, 
    length: { maximum:10 }
    
    validates_numericality_of :price, on: :create, message: "is not a number"
  
     
end

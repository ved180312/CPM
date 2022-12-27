# frozen_string_literal: true

class AddUserIdToCustomerDetails < ActiveRecord::Migration[7.0]
  def change
    add_column :customer_details, :user_id, :integer
    add_index :customer_details, :user_id
  end
end
